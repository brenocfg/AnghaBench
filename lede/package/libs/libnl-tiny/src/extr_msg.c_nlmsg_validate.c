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
struct nla_policy {int dummy; } ;

/* Variables and functions */
 int NLE_MSG_TOOSHORT ; 
 int nla_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nla_policy*) ; 
 int /*<<< orphan*/  nlmsg_attrdata (struct nlmsghdr*,int) ; 
 int /*<<< orphan*/  nlmsg_attrlen (struct nlmsghdr*,int) ; 
 int /*<<< orphan*/  nlmsg_valid_hdr (struct nlmsghdr*,int) ; 

int nlmsg_validate(struct nlmsghdr *nlh, int hdrlen, int maxtype,
		   struct nla_policy *policy)
{
	if (!nlmsg_valid_hdr(nlh, hdrlen))
		return -NLE_MSG_TOOSHORT;

	return nla_validate(nlmsg_attrdata(nlh, hdrlen),
			    nlmsg_attrlen(nlh, hdrlen), maxtype, policy);
}