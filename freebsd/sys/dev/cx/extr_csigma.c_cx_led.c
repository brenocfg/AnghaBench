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
struct TYPE_3__ {int type; int /*<<< orphan*/  bcr0; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ cx_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCR02X_LED ; 
#define  B_SIGMA_2X 128 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cx_led (cx_board_t *b, int on)
{
	switch (b->type) {
	case B_SIGMA_2X:
		if (on) b->bcr0 |= BCR02X_LED;
		else    b->bcr0 &= ~BCR02X_LED;
		outb (BCR0(b->port), b->bcr0);
		break;
	}
}