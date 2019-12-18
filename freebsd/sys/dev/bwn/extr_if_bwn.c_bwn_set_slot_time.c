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
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {scalar_t__ type; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 scalar_t__ BWN_PHYTYPE_G ; 
 int /*<<< orphan*/  BWN_SHARED ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int,scalar_t__) ; 
 int /*<<< orphan*/  bwn_shm_write_2 (struct bwn_mac*,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static void
bwn_set_slot_time(struct bwn_mac *mac, uint16_t time)
{

	/* XXX should exit if 5GHz band .. */
	if (mac->mac_phy.type != BWN_PHYTYPE_G)
		return;

	BWN_WRITE_2(mac, 0x684, 510 + time);
	/* Disabled in Linux b43, can adversely effect performance */
#if 0
	bwn_shm_write_2(mac, BWN_SHARED, 0x0010, time);
#endif
}