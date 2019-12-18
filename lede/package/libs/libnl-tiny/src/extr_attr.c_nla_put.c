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
struct nlattr {int dummy; } ;
struct nl_msg {int /*<<< orphan*/  nm_nlh; } ;

/* Variables and functions */
 int NLE_NOMEM ; 
 int /*<<< orphan*/  NL_DBG (int,char*,struct nl_msg*,int,void*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 struct nlattr* nla_reserve (struct nl_msg*,int,int) ; 
 int nlmsg_data (int /*<<< orphan*/ ) ; 

int nla_put(struct nl_msg *msg, int attrtype, int datalen, const void *data)
{
	struct nlattr *nla;

	nla = nla_reserve(msg, attrtype, datalen);
	if (!nla)
		return -NLE_NOMEM;

	memcpy(nla_data(nla), data, datalen);
	NL_DBG(2, "msg %p: Wrote %d bytes at offset +%td for attr %d\n",
	       msg, datalen, (void *) nla - nlmsg_data(msg->nm_nlh), attrtype);

	return 0;
}