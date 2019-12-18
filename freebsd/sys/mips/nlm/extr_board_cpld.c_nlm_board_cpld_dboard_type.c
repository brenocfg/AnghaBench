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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPLD_CTRL_STATUS ; 
 int nlm_cpld_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nlm_board_cpld_dboard_type(uint64_t base, int slot)
{
	uint16_t val;
	int shift = 0;

	switch (slot) {
	case 0: shift = 0; break;
	case 1: shift = 4; break;
	case 2: shift = 2; break;
	case 3: shift = 6; break;
	}
	val = nlm_cpld_read(base, CPLD_CTRL_STATUS) >> shift;
	return (val & 0x3);
}