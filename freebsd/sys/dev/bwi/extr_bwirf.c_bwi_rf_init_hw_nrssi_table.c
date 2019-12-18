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
typedef  scalar_t__ uint16_t ;
struct bwi_mac {int dummy; } ;
typedef  int int16_t ;

/* Variables and functions */
 int BWI_NRSSI_TBLSZ ; 
 int bwi_nrssi_read (struct bwi_mac*,int) ; 
 int /*<<< orphan*/  bwi_nrssi_write (struct bwi_mac*,int,int) ; 

void
bwi_rf_init_hw_nrssi_table(struct bwi_mac *mac, uint16_t adjust)
{
	int i;

	for (i = 0; i < BWI_NRSSI_TBLSZ; ++i) {
		int16_t val;

		val = bwi_nrssi_read(mac, i);

		val -= adjust;
		if (val < -32)
			val = -32;
		else if (val > 31)
			val = 31;

		bwi_nrssi_write(mac, i, val);
	}
}