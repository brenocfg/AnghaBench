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
struct mfi_softc {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int MFI_FIRMWARE_STATE_CHANGE ; 
 int MFI_FUSION_ENABLE_INTERRUPT_MASK ; 
 int /*<<< orphan*/  MFI_OSTS ; 
 int MFI_READ4 (struct mfi_softc*,int /*<<< orphan*/ ) ; 
 int MFI_STATE_CHANGE_INTERRUPT ; 
 int /*<<< orphan*/  MFI_WRITE4 (struct mfi_softc*,int /*<<< orphan*/ ,int) ; 

int32_t
mfi_tbolt_check_clear_intr_ppc(struct mfi_softc *sc)
{
	int32_t status, mfi_status = 0;

	status = MFI_READ4(sc, MFI_OSTS);

	if (status & 1) {
		MFI_WRITE4(sc, MFI_OSTS, status);
		MFI_READ4(sc, MFI_OSTS);
		if (status & MFI_STATE_CHANGE_INTERRUPT) {
			mfi_status |= MFI_FIRMWARE_STATE_CHANGE;
		}

		return mfi_status;
	}
	if (!(status & MFI_FUSION_ENABLE_INTERRUPT_MASK))
		return 1;

	MFI_READ4(sc, MFI_OSTS);
	return 0;
}