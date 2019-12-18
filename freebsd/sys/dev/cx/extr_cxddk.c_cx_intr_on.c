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
struct TYPE_5__ {int /*<<< orphan*/  bcr0b; scalar_t__ port; TYPE_1__* chan; int /*<<< orphan*/  bcr0; } ;
typedef  TYPE_2__ cx_board_t ;
struct TYPE_4__ {scalar_t__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCR0 (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cx_intr_on (cx_board_t *b)
{
	outb (BCR0(b->port), b->bcr0);
	if (b->chan[8].port || b->chan[12].port)
		outb (BCR0(b->port+0x10), b->bcr0b);
}