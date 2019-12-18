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
struct switch_dev {int ports; } ;
struct switch_attr {int dummy; } ;
struct ip17xx_state {TYPE_2__* regs; } ;
struct TYPE_4__ {int CPU_PORT; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 struct ip17xx_state* get_state (struct switch_dev*) ; 
 int ip_phy_read (struct ip17xx_state*,int,int /*<<< orphan*/ ) ; 
 int ip_phy_write (struct ip17xx_state*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ip17xx_set_port_speed(struct switch_dev *dev, const struct switch_attr *attr, struct switch_val *val)
{
	struct ip17xx_state *state = get_state(dev);
	int nr = val->port_vlan;
	int ctrl;
	int autoneg;
	int speed;
	if (val->value.i == 100) {
		speed = 1;
		autoneg = 0;
	} else if (val->value.i == 10) {
		speed = 0;
		autoneg = 0;
	} else {
		autoneg = 1;
		speed = 1;
	}

	/* Can't set speed for cpu port */
	if (nr == state->regs->CPU_PORT)
		return -EINVAL;

	if (nr >= dev->ports || nr < 0)
		return -EINVAL;

	ctrl = ip_phy_read(state, nr, 0);
	if (ctrl < 0)
		return -EIO;

	ctrl &= (~(1<<12));
	ctrl &= (~(1<<13));
	ctrl |= (autoneg<<12);
	ctrl |= (speed<<13);

	return ip_phy_write(state, nr, 0, ctrl);
}