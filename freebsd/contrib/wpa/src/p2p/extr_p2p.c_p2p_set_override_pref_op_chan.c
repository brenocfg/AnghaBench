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
typedef  void* u8 ;
struct p2p_data {void* override_pref_channel; void* override_pref_op_class; } ;

/* Variables and functions */

void p2p_set_override_pref_op_chan(struct p2p_data *p2p, u8 op_class,
				   u8 chan)
{
	p2p->override_pref_op_class = op_class;
	p2p->override_pref_channel = chan;
}