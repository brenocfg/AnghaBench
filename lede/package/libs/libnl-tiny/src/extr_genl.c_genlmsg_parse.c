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
struct nla_policy {int dummy; } ;
struct genlmsghdr {int dummy; } ;

/* Variables and functions */
 int NLE_MSG_TOOSHORT ; 
 int /*<<< orphan*/  genlmsg_attrdata (struct genlmsghdr*,int) ; 
 int /*<<< orphan*/  genlmsg_attrlen (struct genlmsghdr*,int) ; 
 int /*<<< orphan*/  genlmsg_valid_hdr (struct nlmsghdr*,int) ; 
 int nla_parse (struct nlattr**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nla_policy*) ; 
 struct genlmsghdr* nlmsg_data (struct nlmsghdr*) ; 

int genlmsg_parse(struct nlmsghdr *nlh, int hdrlen, struct nlattr *tb[],
		  int maxtype, struct nla_policy *policy)
{
	struct genlmsghdr *ghdr;

	if (!genlmsg_valid_hdr(nlh, hdrlen))
		return -NLE_MSG_TOOSHORT;

	ghdr = nlmsg_data(nlh);
	return nla_parse(tb, maxtype, genlmsg_attrdata(ghdr, hdrlen),
			 genlmsg_attrlen(ghdr, hdrlen), policy);
}