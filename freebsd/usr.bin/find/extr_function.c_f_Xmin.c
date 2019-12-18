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
struct TYPE_10__ {TYPE_1__* fts_statp; } ;
struct TYPE_8__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_9__ {int flags; TYPE_2__ t_data; } ;
struct TYPE_7__ {int st_ctime; int st_atime; int st_birthtime; int st_mtime; } ;
typedef  TYPE_3__ PLAN ;
typedef  TYPE_4__ FTSENT ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE (int,int /*<<< orphan*/ ) ; 
 int F_TIME_A ; 
 int F_TIME_B ; 
 int F_TIME_C ; 
 int now ; 

int
f_Xmin(PLAN *plan, FTSENT *entry)
{
	if (plan->flags & F_TIME_C) {
		COMPARE((now - entry->fts_statp->st_ctime +
		    60 - 1) / 60, plan->t_data.tv_sec);
	} else if (plan->flags & F_TIME_A) {
		COMPARE((now - entry->fts_statp->st_atime +
		    60 - 1) / 60, plan->t_data.tv_sec);
#if HAVE_STRUCT_STAT_ST_BIRTHTIME
	} else if (plan->flags & F_TIME_B) {
		COMPARE((now - entry->fts_statp->st_birthtime +
		    60 - 1) / 60, plan->t_data.tv_sec);
#endif
	} else {
		COMPARE((now - entry->fts_statp->st_mtime +
		    60 - 1) / 60, plan->t_data.tv_sec);
	}
}