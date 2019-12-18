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

/* Variables and functions */
 int auth_level ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fatalperror (int /*<<< orphan*/ ,char*) ; 
 int fork () ; 
 int /*<<< orphan*/  getptyslave () ; 
 int /*<<< orphan*/  net ; 
 int /*<<< orphan*/  start_login (char*,int,char*) ; 

void
startslave(char *host, int autologin, char *autoname)
{
	int i;

#ifdef	AUTHENTICATION
	if (!autoname || !autoname[0])
		autologin = 0;

	if (autologin < auth_level) {
		fatal(net, "Authorization failed");
		exit(1);
	}
#endif


	if ((i = fork()) < 0)
		fatalperror(net, "fork");
	if (i) {
	} else {
		getptyslave();
		start_login(host, autologin, autoname);
		/*NOTREACHED*/
	}
}