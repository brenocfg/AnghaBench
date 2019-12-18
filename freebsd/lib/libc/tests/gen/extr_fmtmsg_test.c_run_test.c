#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ssize_t ;
typedef  int pid_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ MM_OK ; 
 int STDERR_FILENO ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int dup2 (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ fmtmsg (long,char const*,int,char const*,char const*,char const*) ; 
 int fork () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/ * memchr (char*,char,int) ; 
 int pipe (int*) ; 
 int read (int,char*,int) ; 
 char* realloc (char*,size_t) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
run_test(long classification, const char *label, int severity,
    const char *text, const char *action, const char *tag)
{
	int pip[2];
	pid_t pid, wpid;
	char *result, *p;
	size_t resultsize;
	ssize_t n;
	int status;

	if (pipe(pip) == -1)
		err(2, "pipe");
	pid = fork();
	if (pid == -1)
		err(2, "fork");
	if (pid == 0) {
		close(pip[0]);
		if (pip[1] != STDERR_FILENO &&
		    dup2(pip[1], STDERR_FILENO) == -1)
			_exit(2);
		if (fmtmsg(classification, label, severity, text, action, tag)
		    != MM_OK)
			_exit(1);
		else
			_exit(0);
	}
	close(pip[1]);
	resultsize = 1024;
	result = malloc(resultsize);
	p = result;
	while ((n = read(pip[0], p, result + resultsize - p - 1)) != 0) {
		if (n == -1) {
			if (errno == EINTR)
				continue;
			else
				err(2, "read");
		}
		p += n;
		if (result + resultsize == p - 1) {
			resultsize *= 2;
			result = realloc(result, resultsize);
			if (result == NULL)
				err(2, "realloc");
		}
	}
	if (memchr(result, '\0', p - result) != NULL) {
		free(result);
		return (NULL);
	}
	*p = '\0';
	close(pip[0]);
	while ((wpid = waitpid(pid, &status, 0)) == -1 && errno == EINTR)
		;
	if (wpid == -1)
		err(2, "waitpid");
	if (status != 0) {
		free(result);
		return (NULL);
	}
	return (result);
}