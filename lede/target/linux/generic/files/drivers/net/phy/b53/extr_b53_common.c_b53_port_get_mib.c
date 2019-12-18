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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__* s; } ;
struct switch_val {int port_vlan; int len; TYPE_1__ value; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct b53_mib_desc {int size; char* name; int /*<<< orphan*/  offset; } ;
struct b53_device {int enabled_ports; scalar_t__* buf; } ;

/* Variables and functions */
 scalar_t__ B53_BUF_SIZE ; 
 int /*<<< orphan*/  B53_MIB_PAGE (int) ; 
 int BIT (int) ; 
 struct b53_mib_desc* b53_mibs ; 
 struct b53_mib_desc* b53_mibs_63xx ; 
 struct b53_mib_desc* b53_mibs_65 ; 
 int /*<<< orphan*/  b53_read32 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  b53_read64 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is5365 (struct b53_device*) ; 
 scalar_t__ is63xx (struct b53_device*) ; 
 scalar_t__ snprintf (scalar_t__*,scalar_t__,char*,char*,int /*<<< orphan*/ ) ; 
 struct b53_device* sw_to_b53 (struct switch_dev*) ; 

__attribute__((used)) static int b53_port_get_mib(struct switch_dev *sw_dev,
			    const struct switch_attr *attr,
			    struct switch_val *val)
{
	struct b53_device *dev = sw_to_b53(sw_dev);
	const struct b53_mib_desc *mibs;
	int port = val->port_vlan;
	int len = 0;

	if (!(BIT(port) & dev->enabled_ports))
		return -1;

	if (is5365(dev)) {
		if (port == 5)
			port = 8;

		mibs = b53_mibs_65;
	} else if (is63xx(dev)) {
		mibs = b53_mibs_63xx;
	} else {
		mibs = b53_mibs;
	}

	dev->buf[0] = 0;

	for (; mibs->size > 0; mibs++) {
		u64 val;

		if (mibs->size == 8) {
			b53_read64(dev, B53_MIB_PAGE(port), mibs->offset, &val);
		} else {
			u32 val32;

			b53_read32(dev, B53_MIB_PAGE(port), mibs->offset,
				   &val32);
			val = val32;
		}

		len += snprintf(dev->buf + len, B53_BUF_SIZE - len,
				"%-20s: %llu\n", mibs->name, val);
	}

	val->len = len;
	val->value.s = dev->buf;

	return 0;
}