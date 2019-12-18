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
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct bwi_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  RF_WRITE (struct bwi_mac*,int,int) ; 
 scalar_t__ bwi_rf_lo_devi_measure (struct bwi_mac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t
bwi_rf_get_tp_ctrl2(struct bwi_mac *mac)
{
	uint32_t devi_min;
	uint16_t tp_ctrl2 = 0;
	int i;

	RF_WRITE(mac, 0x52, 0);
	DELAY(10);
	devi_min = bwi_rf_lo_devi_measure(mac, 0);

	for (i = 0; i < 16; ++i) {
		uint32_t devi;

		RF_WRITE(mac, 0x52, i);
		DELAY(10);
		devi = bwi_rf_lo_devi_measure(mac, 0);

		if (devi < devi_min) {
			devi_min = devi;
			tp_ctrl2 = i;
		}
	}
	return tp_ctrl2;
}