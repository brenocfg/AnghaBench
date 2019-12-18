#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * config_rom; } ;
struct fwohci_softc {TYPE_1__ fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWBUSRESET ; 
 int /*<<< orphan*/  FW_GLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  FW_GUNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  OHCI_BUS_OPT ; 
 int /*<<< orphan*/  OHCI_CROMHDR ; 
 int /*<<< orphan*/  OWRITE (struct fwohci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_busreset (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fwohci_task_busreset(void *arg, int pending)
{
	struct fwohci_softc *sc = (struct fwohci_softc *)arg;

	FW_GLOCK(&sc->fc);
	fw_busreset(&sc->fc, FWBUSRESET);
	OWRITE(sc, OHCI_CROMHDR, ntohl(sc->fc.config_rom[0]));
	OWRITE(sc, OHCI_BUS_OPT, ntohl(sc->fc.config_rom[2]));
	FW_GUNLOCK(&sc->fc);
}