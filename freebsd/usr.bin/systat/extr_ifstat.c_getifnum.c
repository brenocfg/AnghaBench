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
typedef  unsigned int u_int ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
#define  CTL_NET 132 
#define  IFMIB_IFCOUNT 131 
#define  IFMIB_SYSTEM 130 
 int /*<<< orphan*/  IFSTAT_ERR (int,char*) ; 
#define  NETLINK_GENERIC 129 
#define  PF_LINK 128 
 scalar_t__ sysctl (int*,int,void*,size_t*,void*,size_t) ; 

__attribute__((used)) static
unsigned int
getifnum(void)
{
	u_int	data    = 0;
	size_t	datalen = 0;
	static	int name[] = { CTL_NET,
			       PF_LINK,
			       NETLINK_GENERIC,
			       IFMIB_SYSTEM,
			       IFMIB_IFCOUNT };

	datalen = sizeof(data);
	if (sysctl(name, 5, (void *)&data, (size_t *)&datalen, (void *)NULL,
	    (size_t)0) != 0)
		IFSTAT_ERR(1, "sysctl error");
	return (data);
}