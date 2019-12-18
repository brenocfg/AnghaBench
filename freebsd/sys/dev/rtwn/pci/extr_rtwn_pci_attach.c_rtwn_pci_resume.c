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
struct rtwn_pci_softc {int /*<<< orphan*/  pc_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct rtwn_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_resume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rtwn_pci_resume(device_t self)
{
	struct rtwn_pci_softc *pc = device_get_softc(self);

	rtwn_resume(&pc->pc_sc);

	return (0);
}