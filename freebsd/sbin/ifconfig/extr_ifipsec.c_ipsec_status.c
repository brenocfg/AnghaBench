#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_3__ {scalar_t__ ifr_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSECGREQID ; 
 TYPE_1__ ifr ; 
 int ioctl (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
ipsec_status(int s)
{
	uint32_t reqid;

	ifr.ifr_data = (caddr_t)&reqid;
	if (ioctl(s, IPSECGREQID, &ifr) == -1)
		return;
	printf("\treqid: %u\n", reqid);
}