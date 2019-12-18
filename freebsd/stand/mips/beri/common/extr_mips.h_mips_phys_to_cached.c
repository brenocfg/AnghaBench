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
typedef  int vaddr_t ;
typedef  int paddr_t ;

/* Variables and functions */
 int MIPS_XKPHYS_CACHED_NC_BASE ; 

__attribute__((used)) static inline vaddr_t
mips_phys_to_cached(paddr_t phys)
{

	return (phys | MIPS_XKPHYS_CACHED_NC_BASE);
}