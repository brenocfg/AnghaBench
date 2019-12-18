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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MFI_OSP0 ; 
 int /*<<< orphan*/  MFI_READ4 (struct mfi_softc*,int /*<<< orphan*/ ) ; 

int32_t
mfi_tbolt_read_fw_status_ppc(struct mfi_softc *sc)
{
	return MFI_READ4(sc, MFI_OSP0);
}