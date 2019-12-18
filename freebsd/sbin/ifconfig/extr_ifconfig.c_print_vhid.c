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
struct ifaddrs {struct if_data* ifa_data; } ;
struct if_data {scalar_t__ ifi_vhid; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 

void
print_vhid(const struct ifaddrs *ifa, const char *s)
{
	struct if_data *ifd;

	if (ifa->ifa_data == NULL)
		return;

	ifd = ifa->ifa_data;
	if (ifd->ifi_vhid == 0)
		return;
	
	printf(" vhid %d", ifd->ifi_vhid);
}