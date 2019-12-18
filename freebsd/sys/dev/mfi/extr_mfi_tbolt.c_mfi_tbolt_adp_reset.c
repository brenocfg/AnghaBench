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
struct mfi_softc {int /*<<< orphan*/  mfi_dev; } ;

/* Variables and functions */
 int DIAG_RESET_ADAPTER ; 
 int DIAG_WRITE_ENABLE ; 
 int /*<<< orphan*/  MFI_HDR ; 
 scalar_t__ MFI_READ4 (struct mfi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MFI_RSR ; 
 int /*<<< orphan*/  MFI_WRITE4 (struct mfi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MFI_WSR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 

int
mfi_tbolt_adp_reset(struct mfi_softc *sc)
{
	int retry = 0, i = 0;
	int HostDiag;

	MFI_WRITE4(sc, MFI_WSR, 0xF);
	MFI_WRITE4(sc, MFI_WSR, 4);
	MFI_WRITE4(sc, MFI_WSR, 0xB);
	MFI_WRITE4(sc, MFI_WSR, 2);
	MFI_WRITE4(sc, MFI_WSR, 7);
	MFI_WRITE4(sc, MFI_WSR, 0xD);

	for (i = 0; i < 10000; i++) ;

	HostDiag = (uint32_t)MFI_READ4(sc, MFI_HDR);

	while (!( HostDiag & DIAG_WRITE_ENABLE)) {
		for (i = 0; i < 1000; i++);
		HostDiag = (uint32_t)MFI_READ4(sc, MFI_HDR);
		device_printf(sc->mfi_dev, "ADP_RESET_TBOLT: retry time=%d, "
		    "hostdiag=%#x\n", retry, HostDiag);

		if (retry++ >= 100)
			return 1;
	}

	device_printf(sc->mfi_dev, "ADP_RESET_TBOLT: HostDiag=%#x\n", HostDiag);

	MFI_WRITE4(sc, MFI_HDR, (HostDiag | DIAG_RESET_ADAPTER));

	for (i=0; i < 10; i++) {
		for (i = 0; i < 10000; i++);
	}

	HostDiag = (uint32_t)MFI_READ4(sc, MFI_RSR);
	while (HostDiag & DIAG_RESET_ADAPTER) {
		for (i = 0; i < 1000; i++) ;
		HostDiag = (uint32_t)MFI_READ4(sc, MFI_RSR);
		device_printf(sc->mfi_dev, "ADP_RESET_TBOLT: retry time=%d, "
		    "hostdiag=%#x\n", retry, HostDiag);

		if (retry++ >= 1000)
			return 1;
	}
	return 0;
}