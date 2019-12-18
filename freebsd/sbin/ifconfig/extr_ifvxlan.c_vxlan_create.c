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
struct ifreq {scalar_t__ ifr_data; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCIFCREATE2 ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  params ; 
 int /*<<< orphan*/  vxlan_check_params () ; 

__attribute__((used)) static void
vxlan_create(int s, struct ifreq *ifr)
{

	vxlan_check_params();

	ifr->ifr_data = (caddr_t) &params;
	if (ioctl(s, SIOCIFCREATE2, ifr) < 0)
		err(1, "SIOCIFCREATE2");
}