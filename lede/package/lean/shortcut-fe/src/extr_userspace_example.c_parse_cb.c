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
 int FAST_CLASSIFIER_A_MAX ; 
 size_t FAST_CLASSIFIER_A_TUPLE ; 
#define  FAST_CLASSIFIER_C_DONE 129 
#define  FAST_CLASSIFIER_C_OFFLOADED 128 
 int NL_OK ; 
 int NL_SKIP ; 
 int /*<<< orphan*/  dump_fc_tuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fast_classifier_genl_policy ; 
 int /*<<< orphan*/  genlmsg_parse (struct nlmsghdr*,int /*<<< orphan*/ ,struct nlattr**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 struct genlmsghdr* nlmsg_data (struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_hdr (struct nl_msg*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int parse_cb(struct nl_msg *msg, void *arg)
{
	struct nlmsghdr *nlh = nlmsg_hdr(msg);
	struct genlmsghdr *gnlh = nlmsg_data(nlh);
	struct nlattr *attrs[FAST_CLASSIFIER_A_MAX];

	genlmsg_parse(nlh, 0, attrs, FAST_CLASSIFIER_A_MAX, fast_classifier_genl_policy);

	switch (gnlh->cmd) {
	case FAST_CLASSIFIER_C_OFFLOADED:
		printf("Got a offloaded message\n");
		dump_fc_tuple(nla_data(attrs[FAST_CLASSIFIER_A_TUPLE]));
		return NL_OK;
	case FAST_CLASSIFIER_C_DONE:
		printf("Got a done message\n");
		dump_fc_tuple(nla_data(attrs[FAST_CLASSIFIER_A_TUPLE]));
		return NL_OK;
	}

	return NL_SKIP;
}