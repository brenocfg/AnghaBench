#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ifreq {scalar_t__ ifr_data; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {scalar_t__ vlr_tag; char* vlr_parent; } ;

/* Variables and functions */
 scalar_t__ NOTAG ; 
 int /*<<< orphan*/  SIOCSETVLAN ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__ params ; 

__attribute__((used)) static void
vlan_set(int s, struct ifreq *ifr)
{
	if (params.vlr_tag != NOTAG && params.vlr_parent[0] != '\0') {
		ifr->ifr_data = (caddr_t) &params;
		if (ioctl(s, SIOCSETVLAN, (caddr_t)ifr) == -1)
			err(1, "SIOCSETVLAN");
	}
}