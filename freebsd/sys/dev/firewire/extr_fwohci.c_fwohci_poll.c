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
struct fwohci_softc {int dummy; } ;
struct firewire_comm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_GLOCK (struct firewire_comm*) ; 
 int /*<<< orphan*/  FW_GUNLOCK (struct firewire_comm*) ; 
 int /*<<< orphan*/  fwohci_check_stat (struct fwohci_softc*) ; 

void
fwohci_poll(struct firewire_comm *fc, int quick, int count)
{
	struct fwohci_softc *sc = (struct fwohci_softc *)fc;

	FW_GLOCK(fc);
	fwohci_check_stat(sc);
	FW_GUNLOCK(fc);
}