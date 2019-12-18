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
 int /*<<< orphan*/  SHELL ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  execl (char*,char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  raw () ; 
 int /*<<< orphan*/  shell_uid () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  unraw () ; 
 char* value (int /*<<< orphan*/ ) ; 
 scalar_t__ wait (int*) ; 

void
shell(int c)
{
	int status;
	char *cp;
	pid_t shpid;

	printf("[sh]\r\n");
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	unraw();
	if ((shpid = fork())) {
		while (shpid != wait(&status));
		raw();
		printf("\r\n!\r\n");
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		return;
	} else {
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if ((cp = strrchr(value(SHELL), '/')) == NULL)
			cp = value(SHELL);
		else
			cp++;
		shell_uid();
		execl(value(SHELL), cp, (char *)NULL);
		printf("\r\ncan't execl!\r\n");
		exit(1);
	}
}