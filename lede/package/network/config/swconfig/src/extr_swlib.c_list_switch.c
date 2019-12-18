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
struct nl_msg {int dummy; } ;
struct genlmsghdr {int dummy; } ;

/* Variables and functions */
 int NL_SKIP ; 
 size_t SWITCH_ATTR_ALIAS ; 
 size_t SWITCH_ATTR_DEV_NAME ; 
 int /*<<< orphan*/  SWITCH_ATTR_MAX ; 
 size_t SWITCH_ATTR_NAME ; 
 int /*<<< orphan*/  genlmsg_attrdata (struct genlmsghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_attrlen (struct genlmsghdr*,int /*<<< orphan*/ ) ; 
 char* nla_get_string (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct genlmsghdr* nlmsg_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_hdr (struct nl_msg*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/ * tb ; 

__attribute__((used)) static int
list_switch(struct nl_msg *msg, void *arg)
{
	struct genlmsghdr *gnlh = nlmsg_data(nlmsg_hdr(msg));

	if (nla_parse(tb, SWITCH_ATTR_MAX, genlmsg_attrdata(gnlh, 0), genlmsg_attrlen(gnlh, 0), NULL) < 0)
		goto done;

	if (!tb[SWITCH_ATTR_DEV_NAME] || !tb[SWITCH_ATTR_NAME])
		goto done;

	printf("Found: %s - %s\n", nla_get_string(tb[SWITCH_ATTR_DEV_NAME]),
		nla_get_string(tb[SWITCH_ATTR_ALIAS]));

done:
	return NL_SKIP;
}