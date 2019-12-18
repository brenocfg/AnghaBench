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
struct TYPE_6__ {scalar_t__ port; TYPE_1__* chan; } ;
typedef  TYPE_2__ cx_board_t ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCR0 (scalar_t__) ; 
 int /*<<< orphan*/  cx_setup_board (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cx_close_board (cx_board_t *b)
{
	cx_setup_board (b, 0, 0, 0);

	/* Reset the controller. */
	outb (BCR0(b->port), 0);
	if (b->chan[8].type || b->chan[12].type)
		outb (BCR0(b->port+0x10), 0);
}