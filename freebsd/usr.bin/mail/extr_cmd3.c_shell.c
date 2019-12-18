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
typedef  int /*<<< orphan*/  sig_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 char* _PATH_CSHELL ; 
 scalar_t__ bangexp (char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  run_command (char*,int /*<<< orphan*/ ,int,int,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlcpy (char*,char*,int) ; 
 char* value (char*) ; 

int
shell(char *str)
{
	sig_t sigint = signal(SIGINT, SIG_IGN);
	char *sh;
	char cmd[BUFSIZ];

	if (strlcpy(cmd, str, sizeof(cmd)) >= sizeof(cmd))
		return (1);
	if (bangexp(cmd, sizeof(cmd)) < 0)
		return (1);
	if ((sh = value("SHELL")) == NULL)
		sh = _PATH_CSHELL;
	(void)run_command(sh, 0, -1, -1, "-c", cmd, NULL);
	(void)signal(SIGINT, sigint);
	printf("!\n");
	return (0);
}