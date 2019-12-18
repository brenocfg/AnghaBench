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
typedef  int u32 ;
struct ena_com_dev {int intr_delay_resolution; TYPE_1__* intr_moder_tbl; } ;
struct TYPE_2__ {int intr_moder_interval; } ;

/* Variables and functions */
 int ENA_COM_FAULT ; 
 size_t ENA_INTR_MODER_LOWEST ; 
 int /*<<< orphan*/  ena_trc_err (char*) ; 

int ena_com_update_nonadaptive_moderation_interval_rx(struct ena_com_dev *ena_dev,
						      u32 rx_coalesce_usecs)
{
	if (!ena_dev->intr_delay_resolution) {
		ena_trc_err("Illegal interrupt delay granularity value\n");
		return ENA_COM_FAULT;
	}

	/* We use LOWEST entry of moderation table for storing
	 * nonadaptive interrupt coalescing values
	 */
	ena_dev->intr_moder_tbl[ENA_INTR_MODER_LOWEST].intr_moder_interval =
		rx_coalesce_usecs / ena_dev->intr_delay_resolution;

	return 0;
}