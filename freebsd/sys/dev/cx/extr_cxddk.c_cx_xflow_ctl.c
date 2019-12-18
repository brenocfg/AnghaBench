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
 int /*<<< orphan*/  STCR (int /*<<< orphan*/ ) ; 
 int STC_SNDSPC ; 
 int STC_SSPC_1 ; 
 int STC_SSPC_2 ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

void cx_xflow_ctl (cx_chan_t *c, int on)
{
	outb (CAR(c->port), c->num & 3);
	outb (STCR(c->port), STC_SNDSPC | (on ? STC_SSPC_1 : STC_SSPC_2));
}