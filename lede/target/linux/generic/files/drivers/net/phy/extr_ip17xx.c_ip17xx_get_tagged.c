#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int i; } ;
struct switch_val {int port_vlan; TYPE_1__ value; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct ip17xx_state {int add_tag; int remove_tag; } ;

/* Variables and functions */
 struct ip17xx_state* get_state (struct switch_dev*) ; 

__attribute__((used)) static int ip17xx_get_tagged(struct switch_dev *dev, const struct switch_attr *attr, struct switch_val *val)
{
	struct ip17xx_state *state = get_state(dev);

	if (state->add_tag & (1<<val->port_vlan)) {
		if (state->remove_tag & (1<<val->port_vlan))
			val->value.i = 3; // shouldn't ever happen.
		else
			val->value.i = 1;
	} else {
		if (state->remove_tag & (1<<val->port_vlan))
			val->value.i = 0;
		else
			val->value.i = 2;
	}
	return 0;
}