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
typedef  int pid_t ;

/* Variables and functions */
 char* AUDITWARN_SCRIPT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  execv (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
auditwarnlog(char *args[])
{
	char *loc_args[9];
	pid_t pid;
	int i;

	loc_args[0] = AUDITWARN_SCRIPT;
	for (i = 0; args[i] != NULL && i < 8; i++)
		loc_args[i+1] = args[i];
	loc_args[i+1] = NULL;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0) {
		/*
		 * Child.
		 */
		execv(AUDITWARN_SCRIPT, loc_args);
		syslog(LOG_ERR, "Could not exec %s (%m)\n",
		    AUDITWARN_SCRIPT);
		exit(1);
	}
	/*
	 * Parent.
	 */
	return (0);
}