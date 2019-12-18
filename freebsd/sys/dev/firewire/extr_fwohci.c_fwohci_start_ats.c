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
struct fwohci_softc {int /*<<< orphan*/  fc; int /*<<< orphan*/  atrs; } ;
struct firewire_comm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_GLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FW_GUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwohci_start (struct fwohci_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fwohci_start_ats(struct firewire_comm *fc)
{
	struct fwohci_softc *sc = (struct fwohci_softc *)fc;
	FW_GLOCK(&sc->fc);
	fwohci_start(sc, &(sc->atrs));
	FW_GUNLOCK(&sc->fc);
	return;
}