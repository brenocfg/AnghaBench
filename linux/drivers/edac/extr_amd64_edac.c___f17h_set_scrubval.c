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
typedef  int u32 ;
struct amd64_pvt {int /*<<< orphan*/  F6; } ;

/* Variables and functions */
 int /*<<< orphan*/  F17H_SCR_BASE_ADDR ; 
 int /*<<< orphan*/  F17H_SCR_LIMIT_ADDR ; 
 int /*<<< orphan*/  pci_write_bits32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void __f17h_set_scrubval(struct amd64_pvt *pvt, u32 scrubval)
{
	/*
	 * Fam17h supports scrub values between 0x5 and 0x14. Also, the values
	 * are shifted down by 0x5, so scrubval 0x5 is written to the register
	 * as 0x0, scrubval 0x6 as 0x1, etc.
	 */
	if (scrubval >= 0x5 && scrubval <= 0x14) {
		scrubval -= 0x5;
		pci_write_bits32(pvt->F6, F17H_SCR_LIMIT_ADDR, scrubval, 0xF);
		pci_write_bits32(pvt->F6, F17H_SCR_BASE_ADDR, 1, 0x1);
	} else {
		pci_write_bits32(pvt->F6, F17H_SCR_BASE_ADDR, 0, 0x1);
	}
}