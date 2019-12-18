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
struct TYPE_3__ {int rts; int num; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ cx_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSVR_RTS (int /*<<< orphan*/ ) ; 
 int MSV_RTS ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

void cx_set_rts (cx_chan_t *c, int on)
{
	c->rts = on ? 1 : 0;
	outb (CAR(c->port), c->num & 3);
	outb (MSVR_RTS(c->port), on ? MSV_RTS : 0);
}