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
typedef  int /*<<< orphan*/  val ;
struct TYPE_2__ {struct switch_val* link; struct switch_val* ports; int /*<<< orphan*/  s; int /*<<< orphan*/  i; } ;
struct switch_val {int /*<<< orphan*/  len; TYPE_1__ value; struct switch_attr const* attr; } ;
struct switch_port_link {int dummy; } ;
struct switch_port {int dummy; } ;
struct switch_dev {int ports; struct switch_val linkbuf; struct switch_val* portbuf; } ;
struct switch_attr {int (* set ) (struct switch_dev*,struct switch_attr const*,struct switch_val*) ;int type; } ;
struct sk_buff {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 size_t SWITCH_ATTR_OP_VALUE_INT ; 
 size_t SWITCH_ATTR_OP_VALUE_LINK ; 
 size_t SWITCH_ATTR_OP_VALUE_PORTS ; 
 size_t SWITCH_ATTR_OP_VALUE_STR ; 
#define  SWITCH_TYPE_INT 132 
#define  SWITCH_TYPE_LINK 131 
#define  SWITCH_TYPE_NOVAL 130 
#define  SWITCH_TYPE_PORTS 129 
#define  SWITCH_TYPE_STRING 128 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct switch_val*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (int /*<<< orphan*/ ) ; 
 int stub1 (struct switch_dev*,struct switch_attr const*,struct switch_val*) ; 
 struct switch_dev* swconfig_get_dev (struct genl_info*) ; 
 struct switch_attr* swconfig_lookup_attr (struct switch_dev*,struct genl_info*,struct switch_val*) ; 
 int swconfig_parse_link (struct sk_buff*,int /*<<< orphan*/ ,struct switch_val*) ; 
 int swconfig_parse_ports (struct sk_buff*,int /*<<< orphan*/ ,struct switch_val*,int) ; 
 int /*<<< orphan*/  swconfig_put_dev (struct switch_dev*) ; 

__attribute__((used)) static int
swconfig_set_attr(struct sk_buff *skb, struct genl_info *info)
{
	const struct switch_attr *attr;
	struct switch_dev *dev;
	struct switch_val val;
	int err = -EINVAL;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	dev = swconfig_get_dev(info);
	if (!dev)
		return -EINVAL;

	memset(&val, 0, sizeof(val));
	attr = swconfig_lookup_attr(dev, info, &val);
	if (!attr || !attr->set)
		goto error;

	val.attr = attr;
	switch (attr->type) {
	case SWITCH_TYPE_NOVAL:
		break;
	case SWITCH_TYPE_INT:
		if (!info->attrs[SWITCH_ATTR_OP_VALUE_INT])
			goto error;
		val.value.i =
			nla_get_u32(info->attrs[SWITCH_ATTR_OP_VALUE_INT]);
		break;
	case SWITCH_TYPE_STRING:
		if (!info->attrs[SWITCH_ATTR_OP_VALUE_STR])
			goto error;
		val.value.s =
			nla_data(info->attrs[SWITCH_ATTR_OP_VALUE_STR]);
		break;
	case SWITCH_TYPE_PORTS:
		val.value.ports = dev->portbuf;
		memset(dev->portbuf, 0,
			sizeof(struct switch_port) * dev->ports);

		/* TODO: implement multipart? */
		if (info->attrs[SWITCH_ATTR_OP_VALUE_PORTS]) {
			err = swconfig_parse_ports(skb,
				info->attrs[SWITCH_ATTR_OP_VALUE_PORTS],
				&val, dev->ports);
			if (err < 0)
				goto error;
		} else {
			val.len = 0;
			err = 0;
		}
		break;
	case SWITCH_TYPE_LINK:
		val.value.link = &dev->linkbuf;
		memset(&dev->linkbuf, 0, sizeof(struct switch_port_link));

		if (info->attrs[SWITCH_ATTR_OP_VALUE_LINK]) {
			err = swconfig_parse_link(skb,
						  info->attrs[SWITCH_ATTR_OP_VALUE_LINK],
						  val.value.link);
			if (err < 0)
				goto error;
		} else {
			val.len = 0;
			err = 0;
		}
		break;
	default:
		goto error;
	}

	err = attr->set(dev, attr, &val);
error:
	swconfig_put_dev(dev);
	return err;
}