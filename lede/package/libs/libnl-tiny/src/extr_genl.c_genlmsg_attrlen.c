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
struct genlmsghdr {int dummy; } ;

/* Variables and functions */
 int NLMSG_ALIGN (int) ; 
 int genlmsg_len (struct genlmsghdr const*) ; 

int genlmsg_attrlen(const struct genlmsghdr *gnlh, int hdrlen)
{
	return genlmsg_len(gnlh) - NLMSG_ALIGN(hdrlen);
}