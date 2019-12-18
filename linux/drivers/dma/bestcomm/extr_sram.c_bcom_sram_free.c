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
struct TYPE_2__ {void* base_virt; int /*<<< orphan*/  lock; int /*<<< orphan*/  rh; } ;

/* Variables and functions */
 TYPE_1__* bcom_sram ; 
 int /*<<< orphan*/  rh_free (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void bcom_sram_free(void *ptr)
{
	unsigned long offset;

	if (!ptr)
		return;

	offset = ptr - bcom_sram->base_virt;

	spin_lock(&bcom_sram->lock);
	rh_free(bcom_sram->rh, offset);
	spin_unlock(&bcom_sram->lock);
}