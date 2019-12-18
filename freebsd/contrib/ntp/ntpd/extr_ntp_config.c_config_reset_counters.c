#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int i; struct TYPE_5__* link; } ;
typedef  TYPE_1__ int_node ;
struct TYPE_6__ {int /*<<< orphan*/  reset_counters; } ;
typedef  TYPE_2__ config_tree ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 TYPE_1__* HEAD_PFIFO (int /*<<< orphan*/ ) ; 
#define  T_Allpeers 134 
#define  T_Auth 133 
#define  T_Ctl 132 
#define  T_Io 131 
#define  T_Mem 130 
#define  T_Sys 129 
#define  T_Timer 128 
 int /*<<< orphan*/  ctl_clr_stats () ; 
 int /*<<< orphan*/  io_clr_stats () ; 
 int /*<<< orphan*/  keyword (int) ; 
 int /*<<< orphan*/  peer_all_reset () ; 
 int /*<<< orphan*/  peer_clr_stats () ; 
 int /*<<< orphan*/  proto_clr_stats () ; 
 int /*<<< orphan*/  reset_auth_stats () ; 
 int /*<<< orphan*/  timer_clr_stats () ; 

__attribute__((used)) static void
config_reset_counters(
	config_tree *ptree
	)
{
	int_node *counter_set;

	for (counter_set = HEAD_PFIFO(ptree->reset_counters);
	     counter_set != NULL;
	     counter_set = counter_set->link) {
		switch (counter_set->i) {
		default:
			DPRINTF(1, ("config_reset_counters %s (%d) invalid\n",
				    keyword(counter_set->i), counter_set->i));
			break;

		case T_Allpeers:
			peer_all_reset();
			break;

		case T_Auth:
			reset_auth_stats();
			break;

		case T_Ctl:
			ctl_clr_stats();
			break;

		case T_Io:
			io_clr_stats();
			break;

		case T_Mem:
			peer_clr_stats();
			break;

		case T_Sys:
			proto_clr_stats();
			break;

		case T_Timer:
			timer_clr_stats();
			break;
		}
	}
}