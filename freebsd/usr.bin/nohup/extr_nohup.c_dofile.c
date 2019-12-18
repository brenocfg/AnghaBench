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
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_MISC ; 
 char* FILENAME ; 
 int MAXPATHLEN ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 char* getenv (char*) ; 
 int open (char const*,int,int) ; 
 scalar_t__ snprintf (char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
dofile(void)
{
	int fd;
	char path[MAXPATHLEN];
	const char *p;

	/*
	 * POSIX mandates if the standard output is a terminal, the standard
	 * output is appended to nohup.out in the working directory.  Failing
	 * that, it will be appended to nohup.out in the directory obtained
	 * from the HOME environment variable.  If file creation is required,
	 * the mode_t is set to S_IRUSR | S_IWUSR.
	 */
	p = FILENAME;
	fd = open(p, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd != -1)
		goto dupit;
	if ((p = getenv("HOME")) != NULL && *p != '\0' &&
	    (size_t)snprintf(path, sizeof(path), "%s/%s", p, FILENAME) <
	    sizeof(path)) {
		fd = open(p = path, O_RDWR | O_CREAT | O_APPEND,
		    S_IRUSR | S_IWUSR);
		if (fd != -1)
			goto dupit;
	}
	errx(EXIT_MISC, "can't open a nohup.out file");

dupit:
	if (dup2(fd, STDOUT_FILENO) == -1)
		err(EXIT_MISC, NULL);
	(void)fprintf(stderr, "appending output to %s\n", p);
}