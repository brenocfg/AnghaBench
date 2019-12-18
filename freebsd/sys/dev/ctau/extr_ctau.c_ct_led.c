#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; int /*<<< orphan*/  e1cfg; int /*<<< orphan*/  port; int /*<<< orphan*/  gmd2; } ;
typedef  TYPE_1__ ct_board_t ;

/* Variables and functions */
#define  B_TAU2_G703 130 
#define  B_TAU_G703 129 
#define  B_TAU_G703C 128 
 int /*<<< orphan*/  E1CFG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1CFG_LED ; 
 int /*<<< orphan*/  GMD2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GMD2_LED ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ct_led (ct_board_t *b, int on)
{
	switch (b->type) {
	case B_TAU_G703:
	case B_TAU_G703C:
	case B_TAU2_G703:
		if (on) b->gmd2 |= GMD2_LED;
		else	b->gmd2 &= ~GMD2_LED;
		outb (GMD2(b->port), b->gmd2);
		break;
	default:
		if (on) b->e1cfg |= E1CFG_LED;
		else	b->e1cfg &= ~E1CFG_LED;
		outb (E1CFG(b->port), b->e1cfg);
		break;
	}
}