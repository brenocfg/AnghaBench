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
struct nlmsghdr {int /*<<< orphan*/  nlmsg_pid; int /*<<< orphan*/  nlmsg_seq; int /*<<< orphan*/  nlmsg_flags; int /*<<< orphan*/  nlmsg_type; } ;
struct nl_msg {struct nlmsghdr* nm_nlh; } ;

/* Variables and functions */
 struct nl_msg* nlmsg_alloc () ; 

struct nl_msg *nlmsg_inherit(struct nlmsghdr *hdr)
{
	struct nl_msg *nm;

	nm = nlmsg_alloc();
	if (nm && hdr) {
		struct nlmsghdr *new = nm->nm_nlh;

		new->nlmsg_type = hdr->nlmsg_type;
		new->nlmsg_flags = hdr->nlmsg_flags;
		new->nlmsg_seq = hdr->nlmsg_seq;
		new->nlmsg_pid = hdr->nlmsg_pid;
	}

	return nm;
}