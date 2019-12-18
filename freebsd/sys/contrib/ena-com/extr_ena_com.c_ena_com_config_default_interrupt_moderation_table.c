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
struct ena_intr_moder_entry {int /*<<< orphan*/  bytes_per_interval; int /*<<< orphan*/  pkts_per_interval; int /*<<< orphan*/  intr_moder_interval; } ;
struct ena_com_dev {struct ena_intr_moder_entry* intr_moder_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_INTR_HIGHEST_BYTES ; 
 int /*<<< orphan*/  ENA_INTR_HIGHEST_PKTS ; 
 int /*<<< orphan*/  ENA_INTR_HIGHEST_USECS ; 
 int /*<<< orphan*/  ENA_INTR_HIGH_BYTES ; 
 int /*<<< orphan*/  ENA_INTR_HIGH_PKTS ; 
 int /*<<< orphan*/  ENA_INTR_HIGH_USECS ; 
 int /*<<< orphan*/  ENA_INTR_LOWEST_BYTES ; 
 int /*<<< orphan*/  ENA_INTR_LOWEST_PKTS ; 
 int /*<<< orphan*/  ENA_INTR_LOWEST_USECS ; 
 int /*<<< orphan*/  ENA_INTR_LOW_BYTES ; 
 int /*<<< orphan*/  ENA_INTR_LOW_PKTS ; 
 int /*<<< orphan*/  ENA_INTR_LOW_USECS ; 
 int /*<<< orphan*/  ENA_INTR_MID_BYTES ; 
 int /*<<< orphan*/  ENA_INTR_MID_PKTS ; 
 int /*<<< orphan*/  ENA_INTR_MID_USECS ; 
 size_t ENA_INTR_MODER_HIGH ; 
 size_t ENA_INTR_MODER_HIGHEST ; 
 size_t ENA_INTR_MODER_LOW ; 
 size_t ENA_INTR_MODER_LOWEST ; 
 size_t ENA_INTR_MODER_MID ; 

void ena_com_config_default_interrupt_moderation_table(struct ena_com_dev *ena_dev)
{
	struct ena_intr_moder_entry *intr_moder_tbl = ena_dev->intr_moder_tbl;

	if (!intr_moder_tbl)
		return;

	intr_moder_tbl[ENA_INTR_MODER_LOWEST].intr_moder_interval =
		ENA_INTR_LOWEST_USECS;
	intr_moder_tbl[ENA_INTR_MODER_LOWEST].pkts_per_interval =
		ENA_INTR_LOWEST_PKTS;
	intr_moder_tbl[ENA_INTR_MODER_LOWEST].bytes_per_interval =
		ENA_INTR_LOWEST_BYTES;

	intr_moder_tbl[ENA_INTR_MODER_LOW].intr_moder_interval =
		ENA_INTR_LOW_USECS;
	intr_moder_tbl[ENA_INTR_MODER_LOW].pkts_per_interval =
		ENA_INTR_LOW_PKTS;
	intr_moder_tbl[ENA_INTR_MODER_LOW].bytes_per_interval =
		ENA_INTR_LOW_BYTES;

	intr_moder_tbl[ENA_INTR_MODER_MID].intr_moder_interval =
		ENA_INTR_MID_USECS;
	intr_moder_tbl[ENA_INTR_MODER_MID].pkts_per_interval =
		ENA_INTR_MID_PKTS;
	intr_moder_tbl[ENA_INTR_MODER_MID].bytes_per_interval =
		ENA_INTR_MID_BYTES;

	intr_moder_tbl[ENA_INTR_MODER_HIGH].intr_moder_interval =
		ENA_INTR_HIGH_USECS;
	intr_moder_tbl[ENA_INTR_MODER_HIGH].pkts_per_interval =
		ENA_INTR_HIGH_PKTS;
	intr_moder_tbl[ENA_INTR_MODER_HIGH].bytes_per_interval =
		ENA_INTR_HIGH_BYTES;

	intr_moder_tbl[ENA_INTR_MODER_HIGHEST].intr_moder_interval =
		ENA_INTR_HIGHEST_USECS;
	intr_moder_tbl[ENA_INTR_MODER_HIGHEST].pkts_per_interval =
		ENA_INTR_HIGHEST_PKTS;
	intr_moder_tbl[ENA_INTR_MODER_HIGHEST].bytes_per_interval =
		ENA_INTR_HIGHEST_BYTES;
}