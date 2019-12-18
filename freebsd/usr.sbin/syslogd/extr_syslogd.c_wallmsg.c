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
struct utmpx {scalar_t__ ut_type; int /*<<< orphan*/  ut_line; int /*<<< orphan*/  ut_user; } ;
struct iovec {int dummy; } ;
struct filed {scalar_t__ f_type; int /*<<< orphan*/ ** fu_uname; } ;

/* Variables and functions */
 scalar_t__ F_WALL ; 
 int MAXUNAMES ; 
 int /*<<< orphan*/  TTYMSGTIME ; 
 scalar_t__ USER_PROCESS ; 
 int /*<<< orphan*/  endutxent () ; 
 scalar_t__ errno ; 
 struct utmpx* getutxent () ; 
 int /*<<< orphan*/  logerror (char const*) ; 
 int /*<<< orphan*/  setutxent () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* ttymsg (struct iovec*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* ttymsg_check (struct iovec*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wallmsg(struct filed *f, struct iovec *iov, const int iovlen)
{
	static int reenter;			/* avoid calling ourselves */
	struct utmpx *ut;
	int i;
	const char *p;

	if (reenter++)
		return;
	setutxent();
	/* NOSTRICT */
	while ((ut = getutxent()) != NULL) {
		if (ut->ut_type != USER_PROCESS)
			continue;
		if (f->f_type == F_WALL) {
			if ((p = ttymsg(iov, iovlen, ut->ut_line,
			    TTYMSGTIME)) != NULL) {
				errno = 0;	/* already in msg */
				logerror(p);
			}
			continue;
		}
		/* should we send the message to this user? */
		for (i = 0; i < MAXUNAMES; i++) {
			if (!f->fu_uname[i][0])
				break;
			if (!strcmp(f->fu_uname[i], ut->ut_user)) {
				if ((p = ttymsg_check(iov, iovlen, ut->ut_line,
				    TTYMSGTIME)) != NULL) {
					errno = 0;	/* already in msg */
					logerror(p);
				}
				break;
			}
		}
	}
	endutxent();
	reenter = 0;
}