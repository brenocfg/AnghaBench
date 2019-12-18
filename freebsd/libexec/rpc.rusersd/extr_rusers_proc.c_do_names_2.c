#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int utmpidlearr_len; TYPE_5__* utmpidlearr_val; } ;
typedef  TYPE_3__ utmpidlearr ;
typedef  int /*<<< orphan*/  ut ;
struct TYPE_9__ {int /*<<< orphan*/  tv_sec; } ;
struct utmpx {scalar_t__ ut_type; int /*<<< orphan*/  ut_host; int /*<<< orphan*/  ut_line; TYPE_1__ ut_tv; } ;
struct TYPE_10__ {int /*<<< orphan*/  ut_host; int /*<<< orphan*/  ut_name; int /*<<< orphan*/  ut_line; int /*<<< orphan*/  ut_time; } ;
struct TYPE_13__ {TYPE_2__ ui_utmp; int /*<<< orphan*/  ui_idle; } ;
struct TYPE_12__ {int /*<<< orphan*/  ut_host; int /*<<< orphan*/  ut_user; int /*<<< orphan*/  ut_line; } ;

/* Variables and functions */
 int MAXUSERS ; 
 scalar_t__ USER_PROCESS ; 
 int /*<<< orphan*/  endutxent () ; 
 int /*<<< orphan*/  getidle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct utmpx* getutxent () ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,struct utmpx*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setutxent () ; 
 TYPE_5__* utmp_idle ; 
 TYPE_4__* utmp_list ; 

__attribute__((used)) static utmpidlearr *
do_names_2(void)
{
	static utmpidlearr ut;
	struct utmpx *usr;
	int nusers = 0;

	memset(&ut, 0, sizeof(ut));
	ut.utmpidlearr_val = &utmp_idle[0];

	setutxent();
	while ((usr = getutxent()) != NULL && nusers < MAXUSERS) {
		if (usr->ut_type != USER_PROCESS)
			continue;

		memcpy(&utmp_list[nusers], usr, sizeof(*usr));
		utmp_idle[nusers].ui_utmp.ut_time = usr->ut_tv.tv_sec;
		utmp_idle[nusers].ui_idle =
		    getidle(usr->ut_line, usr->ut_host);
		utmp_idle[nusers].ui_utmp.ut_line =
		    utmp_list[nusers].ut_line;
		utmp_idle[nusers].ui_utmp.ut_name =
		    utmp_list[nusers].ut_user;
		utmp_idle[nusers].ui_utmp.ut_host =
		    utmp_list[nusers].ut_host;

		nusers++;
	}
	endutxent();

	ut.utmpidlearr_len = nusers;
	return(&ut);
}