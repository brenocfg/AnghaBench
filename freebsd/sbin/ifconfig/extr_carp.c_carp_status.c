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
struct carpreq {int carpr_count; size_t carpr_state; int carpr_vhid; int carpr_advbase; int carpr_advskew; char* carpr_key; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {scalar_t__ ifr_data; } ;

/* Variables and functions */
 int CARP_MAXVHID ; 
 int /*<<< orphan*/  SIOCGVH ; 
 int /*<<< orphan*/  bzero (struct carpreq*,int) ; 
 char** carp_states ; 
 TYPE_1__ ifr ; 
 int ioctl (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ printkeys ; 

__attribute__((used)) static void
carp_status(int s)
{
	struct carpreq carpr[CARP_MAXVHID];
	int i;

	bzero(carpr, sizeof(struct carpreq) * CARP_MAXVHID);
	carpr[0].carpr_count = CARP_MAXVHID;
	ifr.ifr_data = (caddr_t)&carpr;

	if (ioctl(s, SIOCGVH, (caddr_t)&ifr) == -1)
		return;

	for (i = 0; i < carpr[0].carpr_count; i++) {
		printf("\tcarp: %s vhid %d advbase %d advskew %d",
		    carp_states[carpr[i].carpr_state], carpr[i].carpr_vhid,
		    carpr[i].carpr_advbase, carpr[i].carpr_advskew);
		if (printkeys && carpr[i].carpr_key[0] != '\0')
			printf(" key \"%s\"\n", carpr[i].carpr_key);
		else
			printf("\n");
	}
}