#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ txs; } ;
struct TYPE_7__ {int rate; } ;
struct TYPE_8__ {scalar_t__ mode; unsigned long baud; TYPE_1__ hopt; TYPE_2__ gopt; } ;
typedef  TYPE_3__ ct_chan_t ;

/* Variables and functions */
 scalar_t__ CLK_INT ; 
 scalar_t__ M_E1 ; 
 scalar_t__ M_G703 ; 
 unsigned long ct_get_ts (TYPE_3__*) ; 

unsigned long ct_get_baud (ct_chan_t *c)
{
	unsigned long speed;
	unsigned long ts;

	if (c->mode == M_G703) {
		speed = 1000 * c->gopt.rate;
	} else if (c->mode == M_E1) {
		ts = ct_get_ts (c);
		for (speed=0; ts; ts >>= 1) /* Each timeslot is 64 Kbps */
			if (ts & 1)
				speed += 64000;
	} else
		speed = (c->hopt.txs == CLK_INT) ? c->baud : 0;
	return speed;
}