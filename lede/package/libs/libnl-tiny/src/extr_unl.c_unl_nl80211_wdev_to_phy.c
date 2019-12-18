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
struct unl {int dummy; } ;
struct nlattr {int dummy; } ;
struct nl_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_ATTR_IFINDEX ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY ; 
 int /*<<< orphan*/  NL80211_CMD_GET_INTERFACE ; 
 int /*<<< orphan*/  NLA_PUT_U32 (struct nl_msg*,int /*<<< orphan*/ ,int) ; 
 int nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nlmsg_free (struct nl_msg*) ; 
 struct nlattr* unl_find_attr (struct unl*,struct nl_msg*,int /*<<< orphan*/ ) ; 
 struct nl_msg* unl_genl_msg (struct unl*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unl_genl_request_single (struct unl*,struct nl_msg*,struct nl_msg**) ; 

int unl_nl80211_wdev_to_phy(struct unl *unl, int wdev)
{
	struct nl_msg *msg;
	struct nlattr *attr;
	int ret = -1;

	msg = unl_genl_msg(unl, NL80211_CMD_GET_INTERFACE, false);
	if (!msg)
		return -1;

	NLA_PUT_U32(msg, NL80211_ATTR_IFINDEX, wdev);
	if (unl_genl_request_single(unl, msg, &msg) < 0)
		return -1;

	attr = unl_find_attr(unl, msg, NL80211_ATTR_WIPHY);
	if (!attr)
		goto out;

	ret = nla_get_u32(attr);
out:
nla_put_failure:
	nlmsg_free(msg);
	return ret;
}