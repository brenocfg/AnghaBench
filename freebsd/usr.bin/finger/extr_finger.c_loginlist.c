#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct utmpx {scalar_t__ ut_type; int /*<<< orphan*/  ut_user; } ;
struct passwd {int dummy; } ;
struct TYPE_7__ {int (* seq ) (TYPE_2__*,TYPE_1__*,TYPE_1__*,int) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  PERSON ;
typedef  TYPE_1__ DBT ;

/* Variables and functions */
 int R_FIRST ; 
 int R_NEXT ; 
 scalar_t__ USER_PROCESS ; 
 TYPE_2__* db ; 
 int /*<<< orphan*/  endutxent () ; 
 int /*<<< orphan*/  enter_lastlog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * enter_person (struct passwd*) ; 
 int /*<<< orphan*/  enter_where (struct utmpx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/ * find_person (int /*<<< orphan*/ ) ; 
 struct passwd* getpwnam (int /*<<< orphan*/ ) ; 
 struct utmpx* getutxent () ; 
 scalar_t__ hide (struct passwd*) ; 
 scalar_t__ kflag ; 
 scalar_t__ lflag ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setutxent () ; 
 int stub1 (TYPE_2__*,TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static void
loginlist(void)
{
	PERSON *pn;
	DBT data, key;
	struct passwd *pw;
	struct utmpx *user;
	int r, sflag1;

	if (kflag)
		errx(1, "can't list logins without reading utmp");

	setutxent();
	while ((user = getutxent()) != NULL) {
		if (user->ut_type != USER_PROCESS)
			continue;
		if ((pn = find_person(user->ut_user)) == NULL) {
			if ((pw = getpwnam(user->ut_user)) == NULL)
				continue;
			if (hide(pw))
				continue;
			pn = enter_person(pw);
		}
		enter_where(user, pn);
	}
	endutxent();
	if (db && lflag)
		for (sflag1 = R_FIRST;; sflag1 = R_NEXT) {
			PERSON *tmp;

			r = (*db->seq)(db, &key, &data, sflag1);
			if (r == -1)
				err(1, "db seq");
			if (r == 1)
				break;
			memmove(&tmp, data.data, sizeof tmp);
			enter_lastlog(tmp);
		}
}