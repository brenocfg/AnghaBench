#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ct_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  ct_disable_loop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ct_enable_loop (int /*<<< orphan*/ *) ; 

void ct_set_loop (ct_chan_t *c, int on)
{
	if (on)
		ct_enable_loop (c);
	else
		ct_disable_loop (c);
}