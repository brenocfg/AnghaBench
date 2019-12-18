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
 int LOGIN_SETALL ; 
 int LOGIN_SETENV ; 
 int LOGIN_SETGROUP ; 
 int LOGIN_SETLOGIN ; 
 int LOGIN_SETPATH ; 
 int LOGIN_SETUSER ; 
 int /*<<< orphan*/  _exit (int) ; 
 scalar_t__ dowtmp ; 
 int /*<<< orphan*/  ftpd_logwtmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getpwuid (int /*<<< orphan*/ ) ; 
 scalar_t__ logged_in ; 
 int /*<<< orphan*/  seteuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setusercontext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wtmpid ; 

void
dologout(int status)
{

	if (logged_in && dowtmp) {
		(void) seteuid(0);
#ifdef		LOGIN_CAP
 	        setusercontext(NULL, getpwuid(0), 0, LOGIN_SETALL & ~(LOGIN_SETLOGIN |
		       LOGIN_SETUSER | LOGIN_SETGROUP | LOGIN_SETPATH |
		       LOGIN_SETENV));
#endif
		ftpd_logwtmp(wtmpid, NULL, NULL);
	}
	/* beware of flushing buffers after a SIGPIPE */
	_exit(status);
}