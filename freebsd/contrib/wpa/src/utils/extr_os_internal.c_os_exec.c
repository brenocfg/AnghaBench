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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execv (char const*,char**) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_strchr (char*,char) ; 
 char* os_strdup (char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int os_exec(const char *program, const char *arg, int wait_completion)
{
	pid_t pid;
	int pid_status;

	pid = fork();
	if (pid < 0) {
		wpa_printf(MSG_ERROR, "fork: %s", strerror(errno));
		return -1;
	}

	if (pid == 0) {
		/* run the external command in the child process */
		const int MAX_ARG = 30;
		char *_program, *_arg, *pos;
		char *argv[MAX_ARG + 1];
		int i;

		_program = os_strdup(program);
		_arg = os_strdup(arg);

		argv[0] = _program;

		i = 1;
		pos = _arg;
		while (i < MAX_ARG && pos && *pos) {
			while (*pos == ' ')
				pos++;
			if (*pos == '\0')
				break;
			argv[i++] = pos;
			pos = os_strchr(pos, ' ');
			if (pos)
				*pos++ = '\0';
		}
		argv[i] = NULL;

		execv(program, argv);
		wpa_printf(MSG_ERROR, "execv: %s", strerror(errno));
		os_free(_program);
		os_free(_arg);
		exit(0);
		return -1;
	}

	if (wait_completion) {
		/* wait for the child process to complete in the parent */
		waitpid(pid, &pid_status, 0);
	}

	return 0;
}