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
struct genlmsghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENL_HDRLEN ; 
 scalar_t__ NLMSG_ALIGN (int) ; 
 scalar_t__ genlmsg_len (struct genlmsghdr*) ; 
 struct genlmsghdr* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_valid_hdr (struct nlmsghdr*,int /*<<< orphan*/ ) ; 

int genlmsg_valid_hdr(struct nlmsghdr *nlh, int hdrlen)
{
	struct genlmsghdr *ghdr;

	if (!nlmsg_valid_hdr(nlh, GENL_HDRLEN))
		return 0;

	ghdr = nlmsg_data(nlh);
	if (genlmsg_len(ghdr) < NLMSG_ALIGN(hdrlen))
		return 0;

	return 1;
}