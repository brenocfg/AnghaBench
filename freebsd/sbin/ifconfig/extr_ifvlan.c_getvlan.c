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
struct vlanreq {int dummy; } ;
struct ifreq {scalar_t__ ifr_data; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGETVLAN ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
getvlan(int s, struct ifreq *ifr, struct vlanreq *vreq)
{
	bzero((char *)vreq, sizeof(*vreq));
	ifr->ifr_data = (caddr_t)vreq;

	return ioctl(s, SIOCGETVLAN, (caddr_t)ifr);
}