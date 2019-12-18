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
struct bwi_rf {scalar_t__ rf_type; int rf_flags; int /*<<< orphan*/  rf_calib; } ;
struct bwi_mac {struct bwi_rf mac_rf; } ;

/* Variables and functions */
 int BWI_RF_F_INITED ; 
 scalar_t__ BWI_RF_T_BCM2060 ; 
 int /*<<< orphan*/  RF_WRITE (struct bwi_mac*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_rf_init_bcm2050 (struct bwi_mac*) ; 

void
bwi_rf_init(struct bwi_mac *mac)
{
	struct bwi_rf *rf = &mac->mac_rf;

	if (rf->rf_type == BWI_RF_T_BCM2060) {
		/* TODO: 11A */
	} else {
		if (rf->rf_flags & BWI_RF_F_INITED)
			RF_WRITE(mac, 0x78, rf->rf_calib);
		else
			bwi_rf_init_bcm2050(mac);
	}
}