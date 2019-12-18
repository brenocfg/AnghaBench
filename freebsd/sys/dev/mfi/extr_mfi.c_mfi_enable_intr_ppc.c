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
struct mfi_softc {int mfi_flags; } ;

/* Variables and functions */
 int MFI_1078_EIM ; 
 int MFI_FLAGS_1078 ; 
 int MFI_FLAGS_GEN2 ; 
 int MFI_FLAGS_SKINNY ; 
 int MFI_GEN2_EIM ; 
 int /*<<< orphan*/  MFI_ODCR0 ; 
 int /*<<< orphan*/  MFI_OMSK ; 
 int /*<<< orphan*/  MFI_WRITE4 (struct mfi_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mfi_enable_intr_ppc(struct mfi_softc *sc)
{
	if (sc->mfi_flags & MFI_FLAGS_1078) {
		MFI_WRITE4(sc, MFI_ODCR0, 0xFFFFFFFF);
		MFI_WRITE4(sc, MFI_OMSK, ~MFI_1078_EIM);
	}
	else if (sc->mfi_flags & MFI_FLAGS_GEN2) {
		MFI_WRITE4(sc, MFI_ODCR0, 0xFFFFFFFF);
		MFI_WRITE4(sc, MFI_OMSK, ~MFI_GEN2_EIM);
	}
	else if (sc->mfi_flags & MFI_FLAGS_SKINNY) {
		MFI_WRITE4(sc, MFI_OMSK, ~0x00000001);
	}
}