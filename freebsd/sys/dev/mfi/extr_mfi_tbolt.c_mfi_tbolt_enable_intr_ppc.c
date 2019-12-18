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

/* Variables and functions */
 int /*<<< orphan*/  MFI_FUSION_ENABLE_INTERRUPT_MASK ; 
 int /*<<< orphan*/  MFI_OMSK ; 
 int /*<<< orphan*/  MFI_READ4 (struct mfi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MFI_WRITE4 (struct mfi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mfi_tbolt_enable_intr_ppc(struct mfi_softc *sc)
{
	MFI_WRITE4(sc, MFI_OMSK, ~MFI_FUSION_ENABLE_INTERRUPT_MASK);
	MFI_READ4(sc, MFI_OMSK);
}