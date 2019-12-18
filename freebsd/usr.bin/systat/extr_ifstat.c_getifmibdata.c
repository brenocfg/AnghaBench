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
struct ifmibdata {int dummy; } ;

/* Variables and functions */
#define  CTL_NET 132 
 scalar_t__ ENOENT ; 
#define  IFDATA_GENERAL 131 
#define  IFMIB_IFDATA 130 
 int /*<<< orphan*/  IFSTAT_ERR (int,char*) ; 
#define  NETLINK_GENERIC 129 
#define  PF_LINK 128 
 scalar_t__ errno ; 
 scalar_t__ sysctl (int*,int,void*,size_t*,void*,size_t) ; 

__attribute__((used)) static void
getifmibdata(int row, struct ifmibdata *data)
{
	size_t	datalen = 0;
	static	int name[] = { CTL_NET,
			       PF_LINK,
			       NETLINK_GENERIC,
			       IFMIB_IFDATA,
			       0,
			       IFDATA_GENERAL };
	datalen = sizeof(*data);
	name[4] = row;

	if ((sysctl(name, 6, (void *)data, (size_t *)&datalen, (void *)NULL,
	    (size_t)0) != 0) && (errno != ENOENT))
		IFSTAT_ERR(2, "sysctl error getting interface data");
}