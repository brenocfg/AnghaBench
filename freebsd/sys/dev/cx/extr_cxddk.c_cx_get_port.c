#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num; int type; TYPE_1__* board; } ;
typedef  TYPE_2__ cx_chan_t ;
struct TYPE_4__ {scalar_t__ type; int if0type; int if8type; } ;

/* Variables and functions */
 scalar_t__ B_SIGMA_XXX ; 
#define  T_UNIV_RS449 129 
#define  T_UNIV_V35 128 

int cx_get_port (cx_chan_t *c)
{
	int iftype;

	if (c->board->type == B_SIGMA_XXX) {
		switch (c->num) {
		case 0:
			iftype = c->board->if0type; break;
		case 8:
			iftype = c->board->if8type; break;
		default:
			return -1;
		}

		if (iftype)
			switch (c->type) {
			case T_UNIV_V35:   return 1;
			case T_UNIV_RS449: return 2;
			default:	   return -1;
			}
		else
			return 0;
	} else
		return -1;
}