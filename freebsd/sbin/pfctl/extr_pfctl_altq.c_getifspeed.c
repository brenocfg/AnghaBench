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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ifreq {scalar_t__ ifr_data; int /*<<< orphan*/  ifr_name; } ;
struct if_data {scalar_t__ ifi_baudrate; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGIFDATA ; 
 int /*<<< orphan*/  bzero (struct ifreq*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int get_query_socket () ; 
 int ioctl (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int strlcpy (int /*<<< orphan*/ ,char*,int) ; 

u_int32_t
getifspeed(char *ifname)
{
	int		s;
	struct ifreq	ifr;
	struct if_data	ifrdat;

	s = get_query_socket();
	bzero(&ifr, sizeof(ifr));
	if (strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name)) >=
	    sizeof(ifr.ifr_name))
		errx(1, "getifspeed: strlcpy");
	ifr.ifr_data = (caddr_t)&ifrdat;
	if (ioctl(s, SIOCGIFDATA, (caddr_t)&ifr) == -1)
		err(1, "SIOCGIFDATA");
	return ((u_int32_t)ifrdat.ifi_baudrate);
}