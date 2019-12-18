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
struct ena_com_dev {int /*<<< orphan*/ * intr_moder_tbl; int /*<<< orphan*/  dmadev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_MEM_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ena_com_destroy_interrupt_moderation(struct ena_com_dev *ena_dev)
{
	if (ena_dev->intr_moder_tbl)
		ENA_MEM_FREE(ena_dev->dmadev, ena_dev->intr_moder_tbl);
	ena_dev->intr_moder_tbl = NULL;
}