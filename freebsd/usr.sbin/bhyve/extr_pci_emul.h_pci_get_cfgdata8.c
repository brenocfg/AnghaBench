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
typedef  int /*<<< orphan*/  uint8_t ;
struct pci_devinst {scalar_t__ pi_cfgdata; } ;

/* Variables and functions */
 int PCI_REGMAX ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static __inline uint8_t
pci_get_cfgdata8(struct pci_devinst *pi, int offset)
{
	assert(offset <= PCI_REGMAX);
	return (*(uint8_t *)(pi->pi_cfgdata + offset));
}