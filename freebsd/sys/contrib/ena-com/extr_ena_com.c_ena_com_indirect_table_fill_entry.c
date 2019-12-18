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
typedef  int u16 ;
struct ena_rss {int tbl_log_size; int* host_rss_ind_tbl; } ;
struct ena_com_dev {struct ena_rss rss; } ;

/* Variables and functions */
 int ENA_COM_INVAL ; 
 int ENA_TOTAL_NUM_QUEUES ; 
 scalar_t__ unlikely (int) ; 

int ena_com_indirect_table_fill_entry(struct ena_com_dev *ena_dev,
				      u16 entry_idx, u16 entry_value)
{
	struct ena_rss *rss = &ena_dev->rss;

	if (unlikely(entry_idx >= (1 << rss->tbl_log_size)))
		return ENA_COM_INVAL;

	if (unlikely((entry_value > ENA_TOTAL_NUM_QUEUES)))
		return ENA_COM_INVAL;

	rss->host_rss_ind_tbl[entry_idx] = entry_value;

	return 0;
}