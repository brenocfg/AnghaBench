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
struct mfi_softc {int /*<<< orphan*/  mfi_config_lock; } ;

/* Variables and functions */
#define  MFI_DCMD_CFG_ADD 131 
#define  MFI_DCMD_CFG_CLEAR 130 
#define  MFI_DCMD_CFG_FOREIGN_IMPORT 129 
#define  MFI_DCMD_LD_DELETE 128 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mfi_config_lock(struct mfi_softc *sc, uint32_t opcode)
{

	switch (opcode) {
	case MFI_DCMD_LD_DELETE:
	case MFI_DCMD_CFG_ADD:
	case MFI_DCMD_CFG_CLEAR:
	case MFI_DCMD_CFG_FOREIGN_IMPORT:
		sx_xlock(&sc->mfi_config_lock);
		return (1);
	default:
		return (0);
	}
}