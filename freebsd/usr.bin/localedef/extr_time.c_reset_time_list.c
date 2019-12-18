#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * pm; int /*<<< orphan*/ * am; int /*<<< orphan*/ ** weekday; int /*<<< orphan*/ ** wday; int /*<<< orphan*/ ** month; int /*<<< orphan*/ ** mon; } ;

/* Variables and functions */
#define  T_ABDAY 132 
#define  T_ABMON 131 
#define  T_AM_PM 130 
#define  T_DAY 129 
#define  T_MON 128 
 int /*<<< orphan*/  free (char*) ; 
 int last_kw ; 
 TYPE_1__ tm ; 

void
reset_time_list(void)
{
	int i;
	switch (last_kw) {
	case T_ABMON:
		for (i = 0; i < 12; i++) {
			free((char *)tm.mon[i]);
			tm.mon[i] = NULL;
		}
		break;
	case T_MON:
		for (i = 0; i < 12; i++) {
			free((char *)tm.month[i]);
			tm.month[i] = NULL;
		}
		break;
	case T_ABDAY:
		for (i = 0; i < 7; i++) {
			free((char *)tm.wday[i]);
			tm.wday[i] = NULL;
		}
		break;
	case T_DAY:
		for (i = 0; i < 7; i++) {
			free((char *)tm.weekday[i]);
			tm.weekday[i] = NULL;
		}
		break;
	case T_AM_PM:
		free((char *)tm.am);
		tm.am = NULL;
		free((char *)tm.pm);
		tm.pm = NULL;
		break;
	}
}