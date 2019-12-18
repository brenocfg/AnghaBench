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
struct TYPE_2__ {int /*<<< orphan*/ * ports; } ;
struct switch_val {int len; TYPE_1__ value; } ;
struct swconfig_callback {int cmd; struct sk_buff* msg; int /*<<< orphan*/ * nest; int /*<<< orphan*/  (* close ) (struct swconfig_callback*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  fill; struct genl_info* info; } ;
struct sk_buff {int dummy; } ;
struct genl_info {int dummy; } ;
typedef  int /*<<< orphan*/  cb ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (struct swconfig_callback*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_nest_start (struct sk_buff*,int) ; 
 int /*<<< orphan*/  swconfig_close_portlist (struct swconfig_callback*,int /*<<< orphan*/ *) ; 
 int swconfig_send_multipart (struct swconfig_callback*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swconfig_send_port ; 

__attribute__((used)) static int
swconfig_send_ports(struct sk_buff **msg, struct genl_info *info, int attr,
		const struct switch_val *val)
{
	struct swconfig_callback cb;
	int err = 0;
	int i;

	if (!val->value.ports)
		return -EINVAL;

	memset(&cb, 0, sizeof(cb));
	cb.cmd = attr;
	cb.msg = *msg;
	cb.info = info;
	cb.fill = swconfig_send_port;
	cb.close = swconfig_close_portlist;

	cb.nest[0] = nla_nest_start(cb.msg, cb.cmd);
	for (i = 0; i < val->len; i++) {
		err = swconfig_send_multipart(&cb, &val->value.ports[i]);
		if (err)
			goto done;
	}
	err = val->len;
	swconfig_close_portlist(&cb, NULL);
	*msg = cb.msg;

done:
	return err;
}