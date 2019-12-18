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

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  outl (int,int) ; 
 int /*<<< orphan*/  outw (int,int) ; 
 int /*<<< orphan*/  pci_cfgdisable () ; 
 int pci_cfgenable (int,int,int,int,int) ; 
 int /*<<< orphan*/  pcicfg_mtx ; 

__attribute__((used)) static void
pcireg_cfgwrite(int bus, int slot, int func, int reg, int data, int bytes)
{
	int port;

	mtx_lock_spin(&pcicfg_mtx);
	port = pci_cfgenable(bus, slot, func, reg, bytes);
	if (port != 0) {
		switch (bytes) {
		case 1:
			outb(port, data);
			break;
		case 2:
			outw(port, data);
			break;
		case 4:
			outl(port, data);
			break;
		}
		pci_cfgdisable();
	}
	mtx_unlock_spin(&pcicfg_mtx);
}