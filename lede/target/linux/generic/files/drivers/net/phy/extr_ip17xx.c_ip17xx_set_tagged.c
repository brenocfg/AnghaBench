#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int i; } ;
struct switch_val {int port_vlan; TYPE_1__ value; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct ip17xx_state {int add_tag; int remove_tag; TYPE_2__* regs; } ;
struct TYPE_4__ {int (* update_state ) (struct ip17xx_state*) ;} ;

/* Variables and functions */
 struct ip17xx_state* get_state (struct switch_dev*) ; 
 int stub1 (struct ip17xx_state*) ; 

__attribute__((used)) static int ip17xx_set_tagged(struct switch_dev *dev, const struct switch_attr *attr, struct switch_val *val)
{
	struct ip17xx_state *state = get_state(dev);

	state->add_tag &= ~(1<<val->port_vlan);
	state->remove_tag &= ~(1<<val->port_vlan);

	if (val->value.i == 0)
		state->remove_tag |= (1<<val->port_vlan);
	if (val->value.i == 1)
		state->add_tag |= (1<<val->port_vlan);

	return state->regs->update_state(state);
}