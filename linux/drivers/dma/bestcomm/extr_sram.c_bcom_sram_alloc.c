#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ phys_addr_t ;
struct TYPE_2__ {void* base_virt; scalar_t__ base_phys; int /*<<< orphan*/  lock; int /*<<< orphan*/  rh; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_VALUE (unsigned long) ; 
 TYPE_1__* bcom_sram ; 
 unsigned long rh_alloc_align (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void* bcom_sram_alloc(int size, int align, phys_addr_t *phys)
{
	unsigned long offset;

	spin_lock(&bcom_sram->lock);
	offset = rh_alloc_align(bcom_sram->rh, size, align, NULL);
	spin_unlock(&bcom_sram->lock);

	if (IS_ERR_VALUE(offset))
		return NULL;

	*phys = bcom_sram->base_phys + offset;
	return bcom_sram->base_virt + offset;
}