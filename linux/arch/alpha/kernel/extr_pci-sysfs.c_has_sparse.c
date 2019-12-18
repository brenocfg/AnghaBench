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
struct pci_controller {unsigned long sparse_mem_base; unsigned long sparse_io_base; } ;
typedef  enum pci_mmap_state { ____Placeholder_pci_mmap_state } pci_mmap_state ;

/* Variables and functions */
 int pci_mmap_mem ; 

__attribute__((used)) static inline int has_sparse(struct pci_controller *hose,
			     enum pci_mmap_state mmap_type)
{
	unsigned long base;

	base = (mmap_type == pci_mmap_mem) ? hose->sparse_mem_base :
					     hose->sparse_io_base;

	return base != 0;
}