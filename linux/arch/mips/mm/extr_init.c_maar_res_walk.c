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
struct maar_walk_info {size_t num_cfg; struct maar_config* cfg; } ;
struct maar_config {int /*<<< orphan*/  attrs; scalar_t__ upper; int /*<<< orphan*/  lower; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ ALIGN_DOWN (int /*<<< orphan*/ ,unsigned int) ; 
 size_t ARRAY_SIZE (struct maar_config*) ; 
 unsigned int BIT (scalar_t__) ; 
 scalar_t__ MIPS_MAAR_ADDR_SHIFT ; 
 int /*<<< orphan*/  MIPS_MAAR_S ; 
 int /*<<< orphan*/  PFN_PHYS (unsigned long) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int maar_res_walk(unsigned long start_pfn, unsigned long nr_pages,
			 void *data)
{
	struct maar_walk_info *wi = data;
	struct maar_config *cfg = &wi->cfg[wi->num_cfg];
	unsigned int maar_align;

	/* MAAR registers hold physical addresses right shifted by 4 bits */
	maar_align = BIT(MIPS_MAAR_ADDR_SHIFT + 4);

	/* Fill in the MAAR config entry */
	cfg->lower = ALIGN(PFN_PHYS(start_pfn), maar_align);
	cfg->upper = ALIGN_DOWN(PFN_PHYS(start_pfn + nr_pages), maar_align) - 1;
	cfg->attrs = MIPS_MAAR_S;

	/* Ensure we don't overflow the cfg array */
	if (!WARN_ON(wi->num_cfg >= ARRAY_SIZE(wi->cfg)))
		wi->num_cfg++;

	return 0;
}