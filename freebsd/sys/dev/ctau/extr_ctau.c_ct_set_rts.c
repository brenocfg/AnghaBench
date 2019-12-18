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
struct TYPE_3__ {int rts; int /*<<< orphan*/  CTL; } ;
typedef  TYPE_1__ ct_chan_t ;

/* Variables and functions */
 int CTL_RTS_INV ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

void ct_set_rts (ct_chan_t *c, int on)
{
	c->rts = (on != 0);
	if (c->rts)
		outb (c->CTL, inb (c->CTL) & ~CTL_RTS_INV);
	else
		outb (c->CTL, inb (c->CTL) | CTL_RTS_INV);
}