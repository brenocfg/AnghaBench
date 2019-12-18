#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct agp_memory {int type; int page_count; int /*<<< orphan*/ * pages; } ;
typedef  int off_t ;
struct TYPE_9__ {int num_entries; } ;
struct TYPE_8__ {TYPE_2__* dev; int /*<<< orphan*/ * gatt_table; void* current_size; TYPE_1__* driver; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int (* agp_type_to_mask_type ) (TYPE_3__*,int) ;} ;

/* Variables and functions */
 TYPE_5__* A_SIZE_32 (void*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int PAGE_SHIFT ; 
 scalar_t__ __va (int) ; 
 TYPE_3__* agp_bridge ; 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  flush_dcache_range (unsigned long,unsigned long) ; 
 scalar_t__ is_u3 ; 
 int /*<<< orphan*/  mb () ; 
 int page_to_phys (int /*<<< orphan*/ ) ; 
 int scratch_value ; 
 int stub1 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  uninorth_tlbflush (struct agp_memory*) ; 

__attribute__((used)) static int uninorth_insert_memory(struct agp_memory *mem, off_t pg_start, int type)
{
	int i, num_entries;
	void *temp;
	u32 *gp;
	int mask_type;

	if (type != mem->type)
		return -EINVAL;

	mask_type = agp_bridge->driver->agp_type_to_mask_type(agp_bridge, type);
	if (mask_type != 0) {
		/* We know nothing of memory types */
		return -EINVAL;
	}

	if (mem->page_count == 0)
		return 0;

	temp = agp_bridge->current_size;
	num_entries = A_SIZE_32(temp)->num_entries;

	if ((pg_start + mem->page_count) > num_entries)
		return -EINVAL;

	gp = (u32 *) &agp_bridge->gatt_table[pg_start];
	for (i = 0; i < mem->page_count; ++i) {
		if (gp[i] != scratch_value) {
			dev_info(&agp_bridge->dev->dev,
				 "uninorth_insert_memory: entry 0x%x occupied (%x)\n",
				 i, gp[i]);
			return -EBUSY;
		}
	}

	for (i = 0; i < mem->page_count; i++) {
		if (is_u3)
			gp[i] = (page_to_phys(mem->pages[i]) >> PAGE_SHIFT) | 0x80000000UL;
		else
			gp[i] =	cpu_to_le32((page_to_phys(mem->pages[i]) & 0xFFFFF000UL) |
					    0x1UL);
		flush_dcache_range((unsigned long)__va(page_to_phys(mem->pages[i])),
				   (unsigned long)__va(page_to_phys(mem->pages[i]))+0x1000);
	}
	mb();
	uninorth_tlbflush(mem);

	return 0;
}