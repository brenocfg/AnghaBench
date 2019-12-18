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
typedef  int uint8_t ;
struct pt_packet_mode_tsx {int intx; int abrt; } ;

/* Variables and functions */
 int pt_mob_tsx_abrt ; 
 int pt_mob_tsx_intx ; 
 int pte_internal ; 
 int ptps_mode ; 

__attribute__((used)) static int pt_pkt_read_mode_tsx(struct pt_packet_mode_tsx *packet,
				uint8_t mode)
{
	if (!packet)
		return -pte_internal;

	packet->intx = (mode & pt_mob_tsx_intx) != 0;
	packet->abrt = (mode & pt_mob_tsx_abrt) != 0;

	return ptps_mode;
}