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
struct TYPE_4__ {struct switch_port* ports; } ;
struct switch_val {scalar_t__ len; TYPE_2__ value; int /*<<< orphan*/  port_vlan; } ;
struct switch_port {int id; int flags; } ;
struct switch_dev {int dummy; } ;
struct rtl8366_vlan_4k {int member; int untag; } ;
struct rtl8366_smi {int num_ports; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_vlan_4k ) (struct rtl8366_smi*,int /*<<< orphan*/ ,struct rtl8366_vlan_4k*) ;int /*<<< orphan*/  (* is_vlan_valid ) (struct rtl8366_smi*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int SWITCH_PORT_FLAG_TAGGED ; 
 int /*<<< orphan*/  stub1 (struct rtl8366_smi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct rtl8366_smi*,int /*<<< orphan*/ ,struct rtl8366_vlan_4k*) ; 
 struct rtl8366_smi* sw_to_rtl8366_smi (struct switch_dev*) ; 

int rtl8366_sw_get_vlan_ports(struct switch_dev *dev, struct switch_val *val)
{
	struct rtl8366_smi *smi = sw_to_rtl8366_smi(dev);
	struct switch_port *port;
	struct rtl8366_vlan_4k vlan4k;
	int i;

	if (!smi->ops->is_vlan_valid(smi, val->port_vlan))
		return -EINVAL;

	smi->ops->get_vlan_4k(smi, val->port_vlan, &vlan4k);

	port = &val->value.ports[0];
	val->len = 0;
	for (i = 0; i < smi->num_ports; i++) {
		if (!(vlan4k.member & BIT(i)))
			continue;

		port->id = i;
		port->flags = (vlan4k.untag & BIT(i)) ?
					0 : BIT(SWITCH_PORT_FLAG_TAGGED);
		val->len++;
		port++;
	}
	return 0;
}