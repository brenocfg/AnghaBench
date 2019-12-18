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
struct ena_intr_moder_entry {unsigned int intr_moder_interval; } ;
struct ena_com_dev {struct ena_intr_moder_entry* intr_moder_tbl; } ;

/* Variables and functions */
 size_t ENA_INTR_MODER_LOWEST ; 

unsigned int ena_com_get_nonadaptive_moderation_interval_rx(struct ena_com_dev *ena_dev)
{
	struct ena_intr_moder_entry *intr_moder_tbl = ena_dev->intr_moder_tbl;

	if (intr_moder_tbl)
		return intr_moder_tbl[ENA_INTR_MODER_LOWEST].intr_moder_interval;

	return 0;
}