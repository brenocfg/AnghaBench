#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num; scalar_t__ mode; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ cx_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCR_DISTX ; 
 int /*<<< orphan*/  CCR_ENTX ; 
 scalar_t__ M_ASYNC ; 
 int /*<<< orphan*/  STCR (int /*<<< orphan*/ ) ; 
 int STC_ABORTTX ; 
 int STC_SNDSPC ; 
 int /*<<< orphan*/  cx_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cx_transmit_enabled (TYPE_1__*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

void cx_enable_transmit (cx_chan_t *c, int on)
{
	if (cx_transmit_enabled(c) && ! on) {
		outb (CAR(c->port), c->num & 3);
		if (c->mode != M_ASYNC)
			outb (STCR(c->port), STC_ABORTTX | STC_SNDSPC);
		cx_cmd (c->port, CCR_DISTX);
	} else if (! cx_transmit_enabled(c) && on) {
		outb (CAR(c->port), c->num & 3);
		cx_cmd (c->port, CCR_ENTX);
	}
}