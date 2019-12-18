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
struct TYPE_3__ {int num; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ cx_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCR_DISTX ; 
 int /*<<< orphan*/  CCR_ENTX ; 
 int /*<<< orphan*/  cx_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

void cx_transmitter_ctl (cx_chan_t *c,int start)
{
	outb (CAR(c->port), c->num & 3);
	cx_cmd (c->port, start ? CCR_ENTX : CCR_DISTX);
}