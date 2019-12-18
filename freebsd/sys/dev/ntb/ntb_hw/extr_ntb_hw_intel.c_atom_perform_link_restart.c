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
typedef  int uint32_t ;
struct ntb_softc {int dummy; } ;

/* Variables and functions */
 int ATOM_DESKEWSTS_DBERR ; 
 int /*<<< orphan*/  ATOM_DESKEWSTS_OFFSET ; 
 int /*<<< orphan*/  ATOM_ERRCORSTS_OFFSET ; 
 int ATOM_IBIST_ERR_OFLOW ; 
 int /*<<< orphan*/  ATOM_IBSTERRRCRVSTS0_OFFSET ; 
 int /*<<< orphan*/  ATOM_LTSSMERRSTS0_OFFSET ; 
 int ATOM_LTSSMERRSTS0_UNEXPECTEDEI ; 
 int ATOM_LTSSMSTATEJMP_FORCEDETECT ; 
 int /*<<< orphan*/  ATOM_LTSSMSTATEJMP_OFFSET ; 
 int /*<<< orphan*/  ATOM_MODPHY_PCSREG4 ; 
 int /*<<< orphan*/  ATOM_MODPHY_PCSREG6 ; 
 int PCIM_AER_COR_REPLAY_ROLLOVER ; 
 int hz ; 
 int intel_ntb_reg_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ntb_reg_write (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pause (char*,int) ; 

__attribute__((used)) static void
atom_perform_link_restart(struct ntb_softc *ntb)
{
	uint32_t status;

	/* Driver resets the NTB ModPhy lanes - magic! */
	intel_ntb_reg_write(1, ATOM_MODPHY_PCSREG6, 0xe0);
	intel_ntb_reg_write(1, ATOM_MODPHY_PCSREG4, 0x40);
	intel_ntb_reg_write(1, ATOM_MODPHY_PCSREG4, 0x60);
	intel_ntb_reg_write(1, ATOM_MODPHY_PCSREG6, 0x60);

	/* Driver waits 100ms to allow the NTB ModPhy to settle */
	pause("ModPhy", hz / 10);

	/* Clear AER Errors, write to clear */
	status = intel_ntb_reg_read(4, ATOM_ERRCORSTS_OFFSET);
	status &= PCIM_AER_COR_REPLAY_ROLLOVER;
	intel_ntb_reg_write(4, ATOM_ERRCORSTS_OFFSET, status);

	/* Clear unexpected electrical idle event in LTSSM, write to clear */
	status = intel_ntb_reg_read(4, ATOM_LTSSMERRSTS0_OFFSET);
	status |= ATOM_LTSSMERRSTS0_UNEXPECTEDEI;
	intel_ntb_reg_write(4, ATOM_LTSSMERRSTS0_OFFSET, status);

	/* Clear DeSkew Buffer error, write to clear */
	status = intel_ntb_reg_read(4, ATOM_DESKEWSTS_OFFSET);
	status |= ATOM_DESKEWSTS_DBERR;
	intel_ntb_reg_write(4, ATOM_DESKEWSTS_OFFSET, status);

	status = intel_ntb_reg_read(4, ATOM_IBSTERRRCRVSTS0_OFFSET);
	status &= ATOM_IBIST_ERR_OFLOW;
	intel_ntb_reg_write(4, ATOM_IBSTERRRCRVSTS0_OFFSET, status);

	/* Releases the NTB state machine to allow the link to retrain */
	status = intel_ntb_reg_read(4, ATOM_LTSSMSTATEJMP_OFFSET);
	status &= ~ATOM_LTSSMSTATEJMP_FORCEDETECT;
	intel_ntb_reg_write(4, ATOM_LTSSMSTATEJMP_OFFSET, status);
}