#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sc_ic; } ;
struct rtwn_pci_softc {TYPE_1__ pc_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct rtwn_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_stop_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rtwn_pci_shutdown(device_t self)
{
	struct rtwn_pci_softc *pc = device_get_softc(self);

	ieee80211_stop_all(&pc->pc_sc.sc_ic);
	return (0);
}