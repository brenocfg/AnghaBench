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
struct nlmsghdr {int /*<<< orphan*/  nlmsg_len; } ;
struct nl_msg {int /*<<< orphan*/  nm_nlh; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLMSG_ALIGN (int /*<<< orphan*/ ) ; 
 struct nl_msg* __nlmsg_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct nlmsghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct nl_msg*) ; 

struct nl_msg *nlmsg_convert(struct nlmsghdr *hdr)
{
	struct nl_msg *nm;

	nm = __nlmsg_alloc(NLMSG_ALIGN(hdr->nlmsg_len));
	if (!nm)
		goto errout;

	memcpy(nm->nm_nlh, hdr, hdr->nlmsg_len);

	return nm;
errout:
	nlmsg_free(nm);
	return NULL;
}