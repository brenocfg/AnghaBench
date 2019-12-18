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
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cmap1_addr ; 
 int /*<<< orphan*/  cmap1_ptep ; 
 int /*<<< orphan*/  cmap2_addr ; 
 int /*<<< orphan*/  cmap2_ptep ; 
 scalar_t__ crashdumpva ; 
 int /*<<< orphan*/  kernel_pmap ; 
 scalar_t__ pmap_pte (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qmap_addr ; 
 int /*<<< orphan*/  qmap_ptep ; 
 scalar_t__ virtual_avail ; 

__attribute__((used)) static __inline void
pmap_alloc_lmem_map(void)
{
	PCPU_SET(cmap1_addr, virtual_avail);
	PCPU_SET(cmap2_addr, virtual_avail + PAGE_SIZE);
	PCPU_SET(cmap1_ptep, pmap_pte(kernel_pmap, virtual_avail));
	PCPU_SET(cmap2_ptep, pmap_pte(kernel_pmap, virtual_avail + PAGE_SIZE));
	PCPU_SET(qmap_addr, virtual_avail + (2 * PAGE_SIZE));
	PCPU_SET(qmap_ptep, pmap_pte(kernel_pmap, virtual_avail + (2 * PAGE_SIZE)));
	crashdumpva = virtual_avail + (3 * PAGE_SIZE);
	virtual_avail += PAGE_SIZE * 4;
}