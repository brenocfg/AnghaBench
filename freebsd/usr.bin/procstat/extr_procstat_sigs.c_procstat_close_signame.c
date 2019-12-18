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
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int PS_OPT_SIGNUM ; 
 int procstat_opts ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int sys_nsig ; 
 int /*<<< orphan*/ * sys_signame ; 
 char toupper (char) ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 

__attribute__((used)) static void
procstat_close_signame(int sig)
{
	char name[12];
	int i;

	if ((procstat_opts & PS_OPT_SIGNUM) == 0 && sig < sys_nsig) {
		strlcpy(name, sys_signame[sig], sizeof(name));
		for (i = 0; name[i] != 0; i++)
			name[i] = toupper(name[i]);
		xo_close_container(name);
	} else
		snprintf(name, 12, "%d", sig);
		xo_close_container(name);
}