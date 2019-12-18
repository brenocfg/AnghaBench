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
struct ena_extra_properties_strings {int /*<<< orphan*/ * virt_addr; int /*<<< orphan*/  dma_handle; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  size; } ;
struct ena_com_dev {int /*<<< orphan*/  dmadev; struct ena_extra_properties_strings extra_properties_strings; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_MEM_FREE_COHERENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ena_com_delete_extra_properties_strings(struct ena_com_dev *ena_dev)
{
	struct ena_extra_properties_strings *extra_properties_strings =
				&ena_dev->extra_properties_strings;

	if (extra_properties_strings->virt_addr) {
		ENA_MEM_FREE_COHERENT(ena_dev->dmadev,
				      extra_properties_strings->size,
				      extra_properties_strings->virt_addr,
				      extra_properties_strings->dma_addr,
				      extra_properties_strings->dma_handle);
		extra_properties_strings->virt_addr = NULL;
	}
}