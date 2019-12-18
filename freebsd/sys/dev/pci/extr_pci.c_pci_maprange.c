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
typedef  int uint64_t ;

/* Variables and functions */
#define  PCIM_BAR_MEM_1MB 130 
#define  PCIM_BAR_MEM_32 129 
#define  PCIM_BAR_MEM_64 128 
 int PCIM_BAR_MEM_TYPE ; 
 scalar_t__ PCI_BAR_IO (int) ; 

__attribute__((used)) static int
pci_maprange(uint64_t mapreg)
{
	int ln2range = 0;

	if (PCI_BAR_IO(mapreg))
		ln2range = 32;
	else
		switch (mapreg & PCIM_BAR_MEM_TYPE) {
		case PCIM_BAR_MEM_32:
			ln2range = 32;
			break;
		case PCIM_BAR_MEM_1MB:
			ln2range = 20;
			break;
		case PCIM_BAR_MEM_64:
			ln2range = 64;
			break;
		}
	return (ln2range);
}