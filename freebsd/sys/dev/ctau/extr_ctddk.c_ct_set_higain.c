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
struct TYPE_4__ {int higain; } ;
struct TYPE_5__ {scalar_t__ mode; int /*<<< orphan*/  board; TYPE_1__ gopt; } ;
typedef  TYPE_2__ ct_chan_t ;

/* Variables and functions */
 scalar_t__ M_E1 ; 
 int /*<<< orphan*/  ct_setup_e1 (int /*<<< orphan*/ ) ; 

int ct_set_higain (ct_chan_t *c, int on)
{
	if (! (c->mode == M_E1))
		return -1;
	c->gopt.higain = on ? 1 : 0;
	ct_setup_e1 (c->board);
	return 0;
}