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
struct amd_ntb_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_SIDEINFO_OFFSET ; 
 unsigned int AMD_SIDE_READY ; 
 unsigned int amd_ntb_reg_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd_ntb_reg_write (int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
amd_init_side_info(struct amd_ntb_softc *ntb)
{
	unsigned int reg;

	reg = amd_ntb_reg_read(4, AMD_SIDEINFO_OFFSET);
	if (!(reg & AMD_SIDE_READY)) {
		reg |= AMD_SIDE_READY;
		amd_ntb_reg_write(4, AMD_SIDEINFO_OFFSET, reg);
	}
	reg = amd_ntb_reg_read(4, AMD_SIDEINFO_OFFSET);
}