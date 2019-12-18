#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct TYPE_10__ {TYPE_1__* fts_statp; } ;
struct TYPE_8__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_9__ {int flags; TYPE_2__ t_data; } ;
struct TYPE_7__ {int st_atime; int st_birthtime; int st_ctime; int st_mtime; } ;
typedef  TYPE_3__ PLAN ;
typedef  TYPE_4__ FTSENT ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE (int,int /*<<< orphan*/ ) ; 
 int F_EXACTTIME ; 
 int F_TIME_A ; 
 int F_TIME_B ; 
 int F_TIME_C ; 
 int now ; 

int
f_Xtime(PLAN *plan, FTSENT *entry)
{
	time_t xtime;

	if (plan->flags & F_TIME_A)
		xtime = entry->fts_statp->st_atime;
#if HAVE_STRUCT_STAT_ST_BIRTHTIME
	else if (plan->flags & F_TIME_B)
		xtime = entry->fts_statp->st_birthtime;
#endif
	else if (plan->flags & F_TIME_C)
		xtime = entry->fts_statp->st_ctime;
	else
		xtime = entry->fts_statp->st_mtime;

	if (plan->flags & F_EXACTTIME)
		COMPARE(now - xtime, plan->t_data.tv_sec);
	else
		COMPARE((now - xtime + 86400 - 1) / 86400, plan->t_data.tv_sec);
}