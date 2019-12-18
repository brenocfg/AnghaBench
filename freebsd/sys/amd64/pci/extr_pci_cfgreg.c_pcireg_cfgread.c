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
 int inb (int) ; 
 int inl (int) ; 
 int inw (int) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_cfgdisable () ; 
 int pci_cfgenable (int,int,int,int,int) ; 
 int /*<<< orphan*/  pcicfg_mtx ; 

__attribute__((used)) static int
pcireg_cfgread(int bus, int slot, int func, int reg, int bytes)
{
	int data = -1;
	int port;

	mtx_lock_spin(&pcicfg_mtx);
	port = pci_cfgenable(bus, slot, func, reg, bytes);
	if (port != 0) {
		switch (bytes) {
		case 1:
			data = inb(port);
			break;
		case 2:
			data = inw(port);
			break;
		case 4:
			data = inl(port);
			break;
		}
		pci_cfgdisable();
	}
	mtx_unlock_spin(&pcicfg_mtx);
	return (data);
}