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
struct TYPE_5__ {int num; TYPE_1__* board; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ cx_chan_t ;
struct TYPE_4__ {scalar_t__ type; int if0type; int if8type; int /*<<< orphan*/  bcr0b; int /*<<< orphan*/  port; int /*<<< orphan*/  bcr0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCR0_UI_RS449 ; 
 int /*<<< orphan*/  BCR0_UMASK ; 
 scalar_t__ B_SIGMA_XXX ; 
 int /*<<< orphan*/  T_UNIV_RS449 ; 
 int /*<<< orphan*/  T_UNIV_V35 ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cx_set_port (cx_chan_t *c, int iftype)
{
	if (c->board->type == B_SIGMA_XXX) {
		switch (c->num) {
		case 0:
			if ((c->board->if0type != 0) == (iftype != 0))
				return;
			c->board->if0type = iftype;
			c->board->bcr0 &= ~BCR0_UMASK;
			if (c->board->if0type &&
			    (c->type==T_UNIV_RS449 || c->type==T_UNIV_V35))
				c->board->bcr0 |= BCR0_UI_RS449;
			outb (BCR0(c->board->port), c->board->bcr0);
			break;
		case 8:
			if ((c->board->if8type != 0) == (iftype != 0))
				return;
			c->board->if8type = iftype;
			c->board->bcr0b &= ~BCR0_UMASK;
			if (c->board->if8type &&
			    (c->type==T_UNIV_RS449 || c->type==T_UNIV_V35))
				c->board->bcr0b |= BCR0_UI_RS449;
			outb (BCR0(c->board->port+0x10), c->board->bcr0b);
			break;
		}
	}
}