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
typedef  scalar_t__ uid_t ;
typedef  scalar_t__ time_t ;
struct utmpx {scalar_t__ ut_type; char* ut_user; char* ut_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 scalar_t__ USER_PROCESS ; 
 int /*<<< orphan*/  endutxent () ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 struct utmpx* getutxent () ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ term_chk (int,char*,int*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char*,char*) ; 

void
search_utmp(int devfd, char *user, char *tty, char *mytty, uid_t myuid)
{
	struct utmpx *u;
	time_t bestatime, atime;
	int nloggedttys, nttys, msgsok, user_is_me;

	nloggedttys = nttys = 0;
	bestatime = 0;
	user_is_me = 0;

	while ((u = getutxent()) != NULL)
		if (u->ut_type == USER_PROCESS &&
		    strcmp(user, u->ut_user) == 0) {
			++nloggedttys;
			if (term_chk(devfd, u->ut_line, &msgsok, &atime, 0))
				continue;	/* bad term? skip */
			if (myuid && !msgsok)
				continue;	/* skip ttys with msgs off */
			if (strcmp(u->ut_line, mytty) == 0) {
				user_is_me = 1;
				continue;	/* don't write to yourself */
			}
			++nttys;
			if (atime > bestatime) {
				bestatime = atime;
				(void)strlcpy(tty, u->ut_line, MAXPATHLEN);
			}
		}
	endutxent();

	if (nloggedttys == 0)
		errx(1, "%s is not logged in", user);
	if (nttys == 0) {
		if (user_is_me) {		/* ok, so write to yourself! */
			(void)strlcpy(tty, mytty, MAXPATHLEN);
			return;
		}
		errx(1, "%s has messages disabled", user);
	} else if (nttys > 1) {
		warnx("%s is logged in more than once; writing to %s", user, tty);
	}
}