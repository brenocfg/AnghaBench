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
struct swlib_scan_arg {struct switch_dev* ptr; struct switch_dev* head; scalar_t__ name; } ;
struct switch_dev {struct switch_dev* next; void* cpu_port; void* vlans; void* ports; void* name; void* id; void* alias; int /*<<< orphan*/  dev_name; } ;
struct nl_msg {int dummy; } ;
struct genlmsghdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ IFNAMSIZ ; 
 int NL_SKIP ; 
 size_t SWITCH_ATTR_ALIAS ; 
 size_t SWITCH_ATTR_CPU_PORT ; 
 size_t SWITCH_ATTR_DEV_NAME ; 
 size_t SWITCH_ATTR_ID ; 
 int /*<<< orphan*/  SWITCH_ATTR_MAX ; 
 size_t SWITCH_ATTR_NAME ; 
 size_t SWITCH_ATTR_PORTMAP ; 
 size_t SWITCH_ATTR_PORTS ; 
 size_t SWITCH_ATTR_VLANS ; 
 int /*<<< orphan*/  add_port_map (struct switch_dev*,scalar_t__) ; 
 int /*<<< orphan*/  genlmsg_attrdata (struct genlmsghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_attrlen (struct genlmsghdr*,int /*<<< orphan*/ ) ; 
 char const* nla_get_string (scalar_t__) ; 
 void* nla_get_u32 (scalar_t__) ; 
 scalar_t__ nla_parse (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct genlmsghdr* nlmsg_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_hdr (struct nl_msg*) ; 
 int /*<<< orphan*/  refcount ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 struct switch_dev* swlib_alloc (int) ; 
 scalar_t__* tb ; 

__attribute__((used)) static int
add_switch(struct nl_msg *msg, void *arg)
{
	struct swlib_scan_arg *sa = arg;
	struct genlmsghdr *gnlh = nlmsg_data(nlmsg_hdr(msg));
	struct switch_dev *dev;
	const char *name;
	const char *alias;

	if (nla_parse(tb, SWITCH_ATTR_MAX, genlmsg_attrdata(gnlh, 0), genlmsg_attrlen(gnlh, 0), NULL) < 0)
		goto done;

	if (!tb[SWITCH_ATTR_DEV_NAME])
		goto done;

	name = nla_get_string(tb[SWITCH_ATTR_DEV_NAME]);
	alias = nla_get_string(tb[SWITCH_ATTR_ALIAS]);

	if (sa->name && (strcmp(name, sa->name) != 0) && (strcmp(alias, sa->name) != 0))
		goto done;

	dev = swlib_alloc(sizeof(struct switch_dev));
	if (!dev)
		goto done;

	strncpy(dev->dev_name, name, IFNAMSIZ - 1);
	dev->alias = strdup(alias);
	if (tb[SWITCH_ATTR_ID])
		dev->id = nla_get_u32(tb[SWITCH_ATTR_ID]);
	if (tb[SWITCH_ATTR_NAME])
		dev->name = strdup(nla_get_string(tb[SWITCH_ATTR_NAME]));
	if (tb[SWITCH_ATTR_PORTS])
		dev->ports = nla_get_u32(tb[SWITCH_ATTR_PORTS]);
	if (tb[SWITCH_ATTR_VLANS])
		dev->vlans = nla_get_u32(tb[SWITCH_ATTR_VLANS]);
	if (tb[SWITCH_ATTR_CPU_PORT])
		dev->cpu_port = nla_get_u32(tb[SWITCH_ATTR_CPU_PORT]);
	if (tb[SWITCH_ATTR_PORTMAP])
		add_port_map(dev, tb[SWITCH_ATTR_PORTMAP]);

	if (!sa->head) {
		sa->head = dev;
		sa->ptr = dev;
	} else {
		sa->ptr->next = dev;
		sa->ptr = dev;
	}

	refcount++;
done:
	return NL_SKIP;
}