#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  orphan_cmds; } ;
typedef  TYPE_2__ config_tree ;
struct TYPE_6__ {double d; } ;
struct TYPE_8__ {int attr; TYPE_1__ value; struct TYPE_8__* link; } ;
typedef  TYPE_3__ attr_val ;

/* Variables and functions */
 TYPE_3__* HEAD_PFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int PROTO_BCPOLLBSTEP ; 
 int PROTO_BEACON ; 
 int PROTO_CEILING ; 
 int PROTO_COHORT ; 
 int PROTO_FLOOR ; 
 int PROTO_MAXCLOCK ; 
 int PROTO_MAXDIST ; 
 int PROTO_MINCLOCK ; 
 int PROTO_MINDISP ; 
 int PROTO_MINSANE ; 
 int PROTO_ORPHAN ; 
 int PROTO_ORPHWAIT ; 
 int /*<<< orphan*/  STRATUM_UNSPEC ; 
#define  T_Basedate 140 
#define  T_Bcpollbstep 139 
#define  T_Beacon 138 
#define  T_Ceiling 137 
#define  T_Cohort 136 
#define  T_Floor 135 
#define  T_Maxclock 134 
#define  T_Maxdist 133 
#define  T_Minclock 132 
#define  T_Mindist 131 
#define  T_Minsane 130 
#define  T_Orphan 129 
#define  T_Orphanwait 128 
 int /*<<< orphan*/  fatal_error (char*,int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  proto_config (int,int /*<<< orphan*/ ,double,int /*<<< orphan*/ *) ; 
 int sys_maxclock ; 
 int sys_minclock ; 
 int sys_minsane ; 

__attribute__((used)) static void
config_tos(
	config_tree *ptree
	)
{
	attr_val *	tos;
	int		item;
	double		val;

	/* [Bug 2896] For the daemon to work properly it is essential
	 * that minsane < minclock <= maxclock.
	 *
	 * If either constraint is violated, the daemon will be or might
	 * become dysfunctional. Fixing the values is too fragile here,
	 * since three variables with interdependecies are involved. We
	 * just log an error but do not stop: This might be caused by
	 * remote config, and it might be fixed by remote config, too.
	 */
	int l_maxclock = sys_maxclock;
	int l_minclock = sys_minclock;
	int l_minsane  = sys_minsane;

	/* -*- phase one: inspect / sanitize the values */
	tos = HEAD_PFIFO(ptree->orphan_cmds);
	for (; tos != NULL; tos = tos->link) {
		/* not all attributes are doubles (any more), so loading
		 * 'val' in all cases is not a good idea: It should be
		 * done as needed in every case processed here.
		 */
		switch(tos->attr) {
		default:
			break;

		case T_Bcpollbstep:
			val = tos->value.d;
			if (val > 4) {
				msyslog(LOG_WARNING,
					"Using maximum bcpollbstep ceiling %d, %d requested",
					4, (int)val);
				tos->value.d = 4;
			} else if (val < 0) {
				msyslog(LOG_WARNING,
					"Using minimum bcpollbstep floor %d, %d requested",
					0, (int)val);
				tos->value.d = 0;
			}
			break;

		case T_Ceiling:
			val = tos->value.d;
			if (val > STRATUM_UNSPEC - 1) {
				msyslog(LOG_WARNING,
					"Using maximum tos ceiling %d, %d requested",
					STRATUM_UNSPEC - 1, (int)val);
				tos->value.d = STRATUM_UNSPEC - 1;
			} else if (val < 1) {
				msyslog(LOG_WARNING,
					"Using minimum tos floor %d, %d requested",
					1, (int)val);
				tos->value.d = 1;
			}
			break;

		case T_Minclock:
			val = tos->value.d;
			if ((int)tos->value.d < 1)
				tos->value.d = 1;
			l_minclock = (int)tos->value.d;
			break;

		case T_Maxclock:
			val = tos->value.d;
			if ((int)tos->value.d < 1)
				tos->value.d = 1;
			l_maxclock = (int)tos->value.d;
			break;

		case T_Minsane:
			val = tos->value.d;
			if ((int)tos->value.d < 0)
				tos->value.d = 0;
			l_minsane = (int)tos->value.d;
			break;
		}
	}

	if ( ! (l_minsane < l_minclock && l_minclock <= l_maxclock)) {
		msyslog(LOG_ERR,
			"tos error: must have minsane (%d) < minclock (%d) <= maxclock (%d)"
			" - daemon will not operate properly!",
			l_minsane, l_minclock, l_maxclock);
	}

	/* -*- phase two: forward the values to the protocol machinery */
	tos = HEAD_PFIFO(ptree->orphan_cmds);
	for (; tos != NULL; tos = tos->link) {
		switch(tos->attr) {

		default:
			fatal_error("config-tos: attr-token=%d", tos->attr);

		case T_Bcpollbstep:
			item = PROTO_BCPOLLBSTEP;
			break;

		case T_Ceiling:
			item = PROTO_CEILING;
			break;

		case T_Floor:
			item = PROTO_FLOOR;
			break;

		case T_Cohort:
			item = PROTO_COHORT;
			break;

		case T_Orphan:
			item = PROTO_ORPHAN;
			break;

		case T_Orphanwait:
			item = PROTO_ORPHWAIT;
			break;

		case T_Mindist:
			item = PROTO_MINDISP;
			break;

		case T_Maxdist:
			item = PROTO_MAXDIST;
			break;

		case T_Minclock:
			item = PROTO_MINCLOCK;
			break;

		case T_Maxclock:
			item = PROTO_MAXCLOCK;
			break;

		case T_Minsane:
			item = PROTO_MINSANE;
			break;

		case T_Beacon:
			item = PROTO_BEACON;
			break;

		case T_Basedate:
			continue; /* SKIP proto-config for this! */
		}
		proto_config(item, 0, tos->value.d, NULL);
	}
}