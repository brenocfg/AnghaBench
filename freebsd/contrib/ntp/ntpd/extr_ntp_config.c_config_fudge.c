#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct refclockstat {int /*<<< orphan*/  flags; int /*<<< orphan*/  haveflags; int /*<<< orphan*/  fudgeval2; int /*<<< orphan*/  fudgeval1; int /*<<< orphan*/  fudgetime2; int /*<<< orphan*/  fudgetime1; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_8__ {int /*<<< orphan*/  fudge; } ;
typedef  TYPE_2__ config_tree ;
struct TYPE_7__ {int /*<<< orphan*/  i; int /*<<< orphan*/  s; int /*<<< orphan*/  d; } ;
struct TYPE_9__ {int attr; TYPE_1__ value; struct TYPE_9__* link; } ;
typedef  TYPE_3__ attr_val ;
struct TYPE_10__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_4__ address_node ;
struct TYPE_11__ {int /*<<< orphan*/  options; TYPE_4__* addr; struct TYPE_11__* link; } ;
typedef  TYPE_5__ addr_opts_node ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_FLAG1 ; 
 int /*<<< orphan*/  CLK_FLAG2 ; 
 int /*<<< orphan*/  CLK_FLAG3 ; 
 int /*<<< orphan*/  CLK_FLAG4 ; 
 int /*<<< orphan*/  CLK_HAVEFLAG1 ; 
 int /*<<< orphan*/  CLK_HAVEFLAG2 ; 
 int /*<<< orphan*/  CLK_HAVEFLAG3 ; 
 int /*<<< orphan*/  CLK_HAVEFLAG4 ; 
 int /*<<< orphan*/  CLK_HAVETIME1 ; 
 int /*<<< orphan*/  CLK_HAVETIME2 ; 
 int /*<<< orphan*/  CLK_HAVEVAL1 ; 
 int /*<<< orphan*/  CLK_HAVEVAL2 ; 
 void* HEAD_PFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISREFCLOCKADR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
#define  T_Flag1 135 
#define  T_Flag2 134 
#define  T_Flag3 133 
#define  T_Flag4 132 
#define  T_Refid 131 
#define  T_Stratum 130 
#define  T_Time1 129 
#define  T_Time2 128 
 int /*<<< orphan*/  ZERO (struct refclockstat) ; 
 int /*<<< orphan*/  ZERO_SOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getnetnum (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  refclock_control (int /*<<< orphan*/ *,struct refclockstat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t_REF ; 
 int /*<<< orphan*/  token_name (int) ; 

__attribute__((used)) static void
config_fudge(
	config_tree *ptree
	)
{
	addr_opts_node *curr_fudge;
	attr_val *curr_opt;
	sockaddr_u addr_sock;
	address_node *addr_node;
	struct refclockstat clock_stat;
	int err_flag;

	curr_fudge = HEAD_PFIFO(ptree->fudge);
	for (; curr_fudge != NULL; curr_fudge = curr_fudge->link) {
		err_flag = 0;

		/* Get the reference clock address and
		 * ensure that it is sane
		 */
		addr_node = curr_fudge->addr;
		ZERO_SOCK(&addr_sock);
		if (getnetnum(addr_node->address, &addr_sock, 1, t_REF)
		    != 1) {
			err_flag = 1;
			msyslog(LOG_ERR,
				"unrecognized fudge reference clock address %s, line ignored",
				addr_node->address);
		} else if (!ISREFCLOCKADR(&addr_sock)) {
			err_flag = 1;
			msyslog(LOG_ERR,
				"inappropriate address %s for the fudge command, line ignored",
				stoa(&addr_sock));
		}

		/* Parse all the options to the fudge command */
		ZERO(clock_stat);
		curr_opt = HEAD_PFIFO(curr_fudge->options);
		for (; curr_opt != NULL; curr_opt = curr_opt->link) {
			switch (curr_opt->attr) {

			case T_Time1:
				clock_stat.haveflags |= CLK_HAVETIME1;
				clock_stat.fudgetime1 = curr_opt->value.d;
				break;

			case T_Time2:
				clock_stat.haveflags |= CLK_HAVETIME2;
				clock_stat.fudgetime2 = curr_opt->value.d;
				break;

			case T_Stratum:
				clock_stat.haveflags |= CLK_HAVEVAL1;
				clock_stat.fudgeval1 = curr_opt->value.i;
				break;

			case T_Refid:
				clock_stat.haveflags |= CLK_HAVEVAL2;
				clock_stat.fudgeval2 = 0;
				memcpy(&clock_stat.fudgeval2,
				       curr_opt->value.s,
				       min(strlen(curr_opt->value.s), 4));
				break;

			case T_Flag1:
				clock_stat.haveflags |= CLK_HAVEFLAG1;
				if (curr_opt->value.i)
					clock_stat.flags |= CLK_FLAG1;
				else
					clock_stat.flags &= ~CLK_FLAG1;
				break;

			case T_Flag2:
				clock_stat.haveflags |= CLK_HAVEFLAG2;
				if (curr_opt->value.i)
					clock_stat.flags |= CLK_FLAG2;
				else
					clock_stat.flags &= ~CLK_FLAG2;
				break;

			case T_Flag3:
				clock_stat.haveflags |= CLK_HAVEFLAG3;
				if (curr_opt->value.i)
					clock_stat.flags |= CLK_FLAG3;
				else
					clock_stat.flags &= ~CLK_FLAG3;
				break;

			case T_Flag4:
				clock_stat.haveflags |= CLK_HAVEFLAG4;
				if (curr_opt->value.i)
					clock_stat.flags |= CLK_FLAG4;
				else
					clock_stat.flags &= ~CLK_FLAG4;
				break;

			default:
				msyslog(LOG_ERR,
					"Unexpected fudge flag %s (%d) for %s",
					token_name(curr_opt->attr),
					curr_opt->attr, addr_node->address);
				exit(curr_opt->attr ? curr_opt->attr : 1);
			}
		}
# ifdef REFCLOCK
		if (!err_flag)
			refclock_control(&addr_sock, &clock_stat, NULL);
# endif
	}
}