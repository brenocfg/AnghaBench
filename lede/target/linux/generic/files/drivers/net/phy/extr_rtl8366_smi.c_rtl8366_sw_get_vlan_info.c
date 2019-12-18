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
typedef  int u32 ;
struct TYPE_4__ {char* s; } ;
struct switch_val {int len; TYPE_2__ value; int /*<<< orphan*/  port_vlan; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct rtl8366_vlan_4k {int vid; int member; int untag; int fid; } ;
struct rtl8366_smi {char* buf; int num_ports; TYPE_1__* ops; } ;
struct TYPE_3__ {int (* get_vlan_4k ) (struct rtl8366_smi*,int /*<<< orphan*/ ,struct rtl8366_vlan_4k*) ;int /*<<< orphan*/  (* is_vlan_valid ) (struct rtl8366_smi*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int snprintf (char*,int,char*,int,...) ; 
 int /*<<< orphan*/  stub1 (struct rtl8366_smi*,int /*<<< orphan*/ ) ; 
 int stub2 (struct rtl8366_smi*,int /*<<< orphan*/ ,struct rtl8366_vlan_4k*) ; 
 struct rtl8366_smi* sw_to_rtl8366_smi (struct switch_dev*) ; 

int rtl8366_sw_get_vlan_info(struct switch_dev *dev,
			     const struct switch_attr *attr,
			     struct switch_val *val)
{
	int i;
	u32 len = 0;
	struct rtl8366_vlan_4k vlan4k;
	struct rtl8366_smi *smi = sw_to_rtl8366_smi(dev);
	char *buf = smi->buf;
	int err;

	if (!smi->ops->is_vlan_valid(smi, val->port_vlan))
		return -EINVAL;

	memset(buf, '\0', sizeof(smi->buf));

	err = smi->ops->get_vlan_4k(smi, val->port_vlan, &vlan4k);
	if (err)
		return err;

	len += snprintf(buf + len, sizeof(smi->buf) - len,
			"VLAN %d: Ports: '", vlan4k.vid);

	for (i = 0; i < smi->num_ports; i++) {
		if (!(vlan4k.member & (1 << i)))
			continue;

		len += snprintf(buf + len, sizeof(smi->buf) - len, "%d%s", i,
				(vlan4k.untag & (1 << i)) ? "" : "t");
	}

	len += snprintf(buf + len, sizeof(smi->buf) - len,
			"', members=%04x, untag=%04x, fid=%u",
			vlan4k.member, vlan4k.untag, vlan4k.fid);

	val->value.s = buf;
	val->len = len;

	return 0;
}