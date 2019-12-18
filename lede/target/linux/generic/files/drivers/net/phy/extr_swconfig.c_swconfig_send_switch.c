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
typedef  int /*<<< orphan*/  u32 ;
struct switch_dev {int id; int vlans; int ports; int cpu_port; TYPE_1__* portmap; scalar_t__ name; scalar_t__ alias; scalar_t__ devname; } ;
struct sk_buff {int len; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int virt; scalar_t__ s; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  SWITCH_ATTR_ALIAS ; 
 int /*<<< orphan*/  SWITCH_ATTR_CPU_PORT ; 
 int /*<<< orphan*/  SWITCH_ATTR_DEV_NAME ; 
 int /*<<< orphan*/  SWITCH_ATTR_ID ; 
 int /*<<< orphan*/  SWITCH_ATTR_NAME ; 
 int /*<<< orphan*/  SWITCH_ATTR_PORTMAP ; 
 int /*<<< orphan*/  SWITCH_ATTR_PORTS ; 
 int /*<<< orphan*/  SWITCH_ATTR_VLANS ; 
 int /*<<< orphan*/  SWITCH_CMD_NEW_ATTR ; 
 int /*<<< orphan*/  SWITCH_PORTMAP_SEGMENT ; 
 int /*<<< orphan*/  SWITCH_PORTMAP_VIRT ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  switch_fam ; 

__attribute__((used)) static int
swconfig_send_switch(struct sk_buff *msg, u32 pid, u32 seq, int flags,
		const struct switch_dev *dev)
{
	struct nlattr *p = NULL, *m = NULL;
	void *hdr;
	int i;

	hdr = genlmsg_put(msg, pid, seq, &switch_fam, flags,
			SWITCH_CMD_NEW_ATTR);
	if (IS_ERR(hdr))
		return -1;

	if (nla_put_u32(msg, SWITCH_ATTR_ID, dev->id))
		goto nla_put_failure;
	if (nla_put_string(msg, SWITCH_ATTR_DEV_NAME, dev->devname))
		goto nla_put_failure;
	if (nla_put_string(msg, SWITCH_ATTR_ALIAS, dev->alias))
		goto nla_put_failure;
	if (nla_put_string(msg, SWITCH_ATTR_NAME, dev->name))
		goto nla_put_failure;
	if (nla_put_u32(msg, SWITCH_ATTR_VLANS, dev->vlans))
		goto nla_put_failure;
	if (nla_put_u32(msg, SWITCH_ATTR_PORTS, dev->ports))
		goto nla_put_failure;
	if (nla_put_u32(msg, SWITCH_ATTR_CPU_PORT, dev->cpu_port))
		goto nla_put_failure;

	m = nla_nest_start(msg, SWITCH_ATTR_PORTMAP);
	if (!m)
		goto nla_put_failure;
	for (i = 0; i < dev->ports; i++) {
		p = nla_nest_start(msg, SWITCH_ATTR_PORTS);
		if (!p)
			continue;
		if (dev->portmap[i].s) {
			if (nla_put_string(msg, SWITCH_PORTMAP_SEGMENT,
						dev->portmap[i].s))
				goto nla_put_failure;
			if (nla_put_u32(msg, SWITCH_PORTMAP_VIRT,
						dev->portmap[i].virt))
				goto nla_put_failure;
		}
		nla_nest_end(msg, p);
	}
	nla_nest_end(msg, m);
	genlmsg_end(msg, hdr);
	return msg->len;
nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}