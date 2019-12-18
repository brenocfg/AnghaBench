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
typedef  int /*<<< orphan*/  ut ;
struct utmpx {int /*<<< orphan*/  ut_line; int /*<<< orphan*/  ut_id; int /*<<< orphan*/  ut_tv; int /*<<< orphan*/  ut_pid; int /*<<< orphan*/  ut_type; int /*<<< orphan*/  ut_host; int /*<<< orphan*/  ut_user; } ;
struct sockaddr {int /*<<< orphan*/  sa_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEAD_PROCESS ; 
 int /*<<< orphan*/  USER_PROCESS ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct utmpx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pututxline (struct utmpx*) ; 
 int /*<<< orphan*/  realhostname_sa (int /*<<< orphan*/ ,int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

void
ftpd_logwtmp(char *id, char *user, struct sockaddr *addr)
{
	struct utmpx ut;

	memset(&ut, 0, sizeof(ut));

	if (user != NULL) {
		/* Log in. */
		ut.ut_type = USER_PROCESS;
		(void)strncpy(ut.ut_user, user, sizeof(ut.ut_user));
		if (addr != NULL)
			realhostname_sa(ut.ut_host, sizeof(ut.ut_host),
			    addr, addr->sa_len);
	} else {
		/* Log out. */
		ut.ut_type = DEAD_PROCESS;
	}

	ut.ut_pid = getpid();
	gettimeofday(&ut.ut_tv, NULL);
	(void)strncpy(ut.ut_id, id, sizeof(ut.ut_id));
	(void)strncpy(ut.ut_line, "ftpd", sizeof(ut.ut_line));

	pututxline(&ut);
}