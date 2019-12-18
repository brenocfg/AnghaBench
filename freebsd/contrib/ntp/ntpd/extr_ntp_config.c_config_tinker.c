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
struct TYPE_7__ {int /*<<< orphan*/  tinker; } ;
typedef  TYPE_2__ config_tree ;
struct TYPE_6__ {int /*<<< orphan*/  d; } ;
struct TYPE_8__ {int attr; TYPE_1__ value; struct TYPE_8__* link; } ;
typedef  TYPE_3__ attr_val ;

/* Variables and functions */
 TYPE_3__* HEAD_PFIFO (int /*<<< orphan*/ ) ; 
 int LOOP_ALLAN ; 
 int LOOP_FREQ ; 
 int LOOP_HUFFPUFF ; 
 int LOOP_MAX ; 
 int LOOP_MAX_BACK ; 
 int LOOP_MAX_FWD ; 
 int LOOP_MINSTEP ; 
 int LOOP_PANIC ; 
 int LOOP_PHI ; 
 int LOOP_TICK ; 
#define  T_Allan 137 
#define  T_Dispersion 136 
#define  T_Freq 135 
#define  T_Huffpuff 134 
#define  T_Panic 133 
#define  T_Step 132 
#define  T_Stepback 131 
#define  T_Stepfwd 130 
#define  T_Stepout 129 
#define  T_Tick 128 
 int /*<<< orphan*/  fatal_error (char*,int) ; 
 int /*<<< orphan*/  loop_config (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
config_tinker(
	config_tree *ptree
	)
{
	attr_val *	tinker;
	int		item;

	tinker = HEAD_PFIFO(ptree->tinker);
	for (; tinker != NULL; tinker = tinker->link) {
		switch (tinker->attr) {

		default:
			fatal_error("config_tinker: attr-token=%d", tinker->attr);

		case T_Allan:
			item = LOOP_ALLAN;
			break;

		case T_Dispersion:
			item = LOOP_PHI;
			break;

		case T_Freq:
			item = LOOP_FREQ;
			break;

		case T_Huffpuff:
			item = LOOP_HUFFPUFF;
			break;

		case T_Panic:
			item = LOOP_PANIC;
			break;

		case T_Step:
			item = LOOP_MAX;
			break;

		case T_Stepback:
			item = LOOP_MAX_BACK;
			break;

		case T_Stepfwd:
			item = LOOP_MAX_FWD;
			break;

		case T_Stepout:
			item = LOOP_MINSTEP;
			break;

		case T_Tick:
			item = LOOP_TICK;
			break;
		}
		loop_config(item, tinker->value.d);
	}
}