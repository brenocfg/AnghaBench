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
struct msghdr {int dummy; } ;
struct cmsghdr {scalar_t__ cmsg_level; scalar_t__ cmsg_type; scalar_t__ cmsg_len; } ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 scalar_t__ CMSG_FIRSTHDR (struct msghdr*) ; 
 scalar_t__ CMSG_LEN (int) ; 
 scalar_t__ CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 scalar_t__ IPPROTO_IPV6 ; 
 scalar_t__ IPV6_HOPLIMIT ; 

int
get_hoplim(struct msghdr *mhdr)
{
	struct cmsghdr *cm;

	for (cm = (struct cmsghdr *)CMSG_FIRSTHDR(mhdr); cm;
	    cm = (struct cmsghdr *)CMSG_NXTHDR(mhdr, cm)) {
		if (cm->cmsg_level == IPPROTO_IPV6 &&
		    cm->cmsg_type == IPV6_HOPLIMIT &&
		    cm->cmsg_len == CMSG_LEN(sizeof(int)))
			return (*(int *)CMSG_DATA(cm));
	}

	return (-1);
}