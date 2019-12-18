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
struct utmpx {scalar_t__ ut_type; int /*<<< orphan*/  ut_user; int /*<<< orphan*/  ut_line; } ;

/* Variables and functions */
 scalar_t__ USER_PROCESS ; 
 int /*<<< orphan*/  endutxent () ; 
 struct utmpx* getutxline (struct utmpx*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

int
utmp_chk(char *user, char *tty)
{
	struct utmpx lu, *u;

	strncpy(lu.ut_line, tty, sizeof lu.ut_line);
	while ((u = getutxline(&lu)) != NULL)
		if (u->ut_type == USER_PROCESS &&
		    strcmp(user, u->ut_user) == 0) {
			endutxent();
			return(0);
		}
	endutxent();
	return(1);
}