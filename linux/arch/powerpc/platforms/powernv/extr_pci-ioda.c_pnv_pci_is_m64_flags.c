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
 unsigned long IORESOURCE_MEM_64 ; 
 unsigned long IORESOURCE_PREFETCH ; 

__attribute__((used)) static inline bool pnv_pci_is_m64_flags(unsigned long resource_flags)
{
	unsigned long flags = (IORESOURCE_MEM_64 | IORESOURCE_PREFETCH);

	return (resource_flags & flags) == flags;
}