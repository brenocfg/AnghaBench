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
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nl_msg {int dummy; } ;
struct genlmsghdr {int cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL_CLASSIFIER_ATTR_MAX ; 
 size_t NL_CLASSIFIER_ATTR_TUPLE ; 
#define  NL_CLASSIFIER_CMD_ACCEL_OK 129 
#define  NL_CLASSIFIER_CMD_CONNECTION_CLOSED 128 
 int /*<<< orphan*/  NL_CLASSIFIER_GENL_HDRSIZE ; 
 int NL_OK ; 
 int NL_SKIP ; 
 int /*<<< orphan*/  genlmsg_parse (struct nlmsghdr*,int /*<<< orphan*/ ,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl_classifier_dump_nl_tuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl_classifier_genl_policy ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 struct genlmsghdr* nlmsg_data (struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_hdr (struct nl_msg*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int nl_classifier_msg_recv(struct nl_msg *msg, void *arg)
{
	struct nlmsghdr *nlh = nlmsg_hdr(msg);
	struct genlmsghdr *gnlh = nlmsg_data(nlh);
	struct nlattr *attrs[(NL_CLASSIFIER_ATTR_MAX+1)];

	genlmsg_parse(nlh, NL_CLASSIFIER_GENL_HDRSIZE, attrs, NL_CLASSIFIER_ATTR_MAX, nl_classifier_genl_policy);

	switch (gnlh->cmd) {
	case NL_CLASSIFIER_CMD_ACCEL_OK:
		printf("Acceleration successful:\n");
		nl_classifier_dump_nl_tuple(nla_data(attrs[NL_CLASSIFIER_ATTR_TUPLE]));
		return NL_OK;
	case NL_CLASSIFIER_CMD_CONNECTION_CLOSED:
		printf("Connection is closed:\n");
		nl_classifier_dump_nl_tuple(nla_data(attrs[NL_CLASSIFIER_ATTR_TUPLE]));
		return NL_OK;
	default:
		printf("nl classifier received unknow message %d\n", gnlh->cmd);
	}

	return NL_SKIP;
}