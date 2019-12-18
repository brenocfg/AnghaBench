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
struct ntb_softc {scalar_t__ dev_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_MBAR23_OFFSET ; 
 int /*<<< orphan*/  ATOM_MBAR45_OFFSET ; 
 int /*<<< orphan*/  ATOM_PBAR2XLAT_OFFSET ; 
 int /*<<< orphan*/  ATOM_PBAR4XLAT_OFFSET ; 
 scalar_t__ NTB_DEV_USD ; 
 int /*<<< orphan*/  XEON_B2B_BAR2_ADDR64 ; 
 int /*<<< orphan*/  XEON_B2B_BAR4_ADDR64 ; 
 int /*<<< orphan*/  intel_ntb_reg_write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
configure_atom_secondary_side_bars(struct ntb_softc *ntb)
{

	if (ntb->dev_type == NTB_DEV_USD) {
		intel_ntb_reg_write(8, ATOM_PBAR2XLAT_OFFSET,
		    XEON_B2B_BAR2_ADDR64);
		intel_ntb_reg_write(8, ATOM_PBAR4XLAT_OFFSET,
		    XEON_B2B_BAR4_ADDR64);
		intel_ntb_reg_write(8, ATOM_MBAR23_OFFSET, XEON_B2B_BAR2_ADDR64);
		intel_ntb_reg_write(8, ATOM_MBAR45_OFFSET, XEON_B2B_BAR4_ADDR64);
	} else {
		intel_ntb_reg_write(8, ATOM_PBAR2XLAT_OFFSET,
		    XEON_B2B_BAR2_ADDR64);
		intel_ntb_reg_write(8, ATOM_PBAR4XLAT_OFFSET,
		    XEON_B2B_BAR4_ADDR64);
		intel_ntb_reg_write(8, ATOM_MBAR23_OFFSET, XEON_B2B_BAR2_ADDR64);
		intel_ntb_reg_write(8, ATOM_MBAR45_OFFSET, XEON_B2B_BAR4_ADDR64);
	}
}