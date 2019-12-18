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
 int PCI_INVALID_IRQ ; 

__attribute__((used)) static __inline int 
pci_i386_map_intline(int line)
{
	if (line == 0 || line >= 128)
		return (PCI_INVALID_IRQ);
	return (line);
}