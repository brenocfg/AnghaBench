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
struct TYPE_2__ {struct switch_port_link* link; } ;
struct switch_val {TYPE_1__ value; } ;
struct switch_port_link {int /*<<< orphan*/  speed; scalar_t__ aneg; scalar_t__ duplex; } ;
struct nlattr {int dummy; } ;
struct nl_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT_FLAG (struct nl_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLA_PUT_U32 (struct nl_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWITCH_ATTR_OP_VALUE_LINK ; 
 int /*<<< orphan*/  SWITCH_LINK_FLAG_ANEG ; 
 int /*<<< orphan*/  SWITCH_LINK_FLAG_DUPLEX ; 
 int /*<<< orphan*/  SWITCH_LINK_SPEED ; 
 int /*<<< orphan*/  nla_nest_end (struct nl_msg*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct nl_msg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
send_attr_link(struct nl_msg *msg, struct switch_val *val)
{
	struct switch_port_link *link = val->value.link;
	struct nlattr *n;

	n = nla_nest_start(msg, SWITCH_ATTR_OP_VALUE_LINK);
	if (!n)
		goto nla_put_failure;

	if (link->duplex)
		NLA_PUT_FLAG(msg, SWITCH_LINK_FLAG_DUPLEX);
	if (link->aneg)
		NLA_PUT_FLAG(msg, SWITCH_LINK_FLAG_ANEG);
	NLA_PUT_U32(msg, SWITCH_LINK_SPEED, link->speed);

	nla_nest_end(msg, n);

	return 0;

nla_put_failure:
	return -1;
}