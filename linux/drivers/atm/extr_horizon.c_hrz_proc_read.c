#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct atm_dev {int dummy; } ;
typedef  int loff_t ;
struct TYPE_5__ {int tx_avail; int rx_avail; int /*<<< orphan*/  noof_spare_buffers; int /*<<< orphan*/  unassigned_cell_count; int /*<<< orphan*/  hec_error_count; int /*<<< orphan*/  rx_cell_count; int /*<<< orphan*/  tx_cell_count; } ;
typedef  TYPE_1__ hrz_dev ;

/* Variables and functions */
 int /*<<< orphan*/  BUCKET_CAPACITY_ACCESS ; 
 int /*<<< orphan*/  BUCKET_FULLNESS_ACCESS ; 
 int /*<<< orphan*/  DBG_FLOW ; 
 TYPE_1__* HRZ_DEV (struct atm_dev*) ; 
 int /*<<< orphan*/  PRINTD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RX_FREE_BUFFER_COUNT_OFF ; 
 unsigned int TX_CHANS ; 
 int /*<<< orphan*/  TX_FREE_BUFFER_COUNT_OFF ; 
 int query_tx_channel_config (TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rd_regw (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static int hrz_proc_read (struct atm_dev * atm_dev, loff_t * pos, char * page) {
  hrz_dev * dev = HRZ_DEV(atm_dev);
  int left = *pos;
  PRINTD (DBG_FLOW, "hrz_proc_read");
  
  /* more diagnostics here? */
  
#if 0
  if (!left--) {
    unsigned int count = sprintf (page, "vbr buckets:");
    unsigned int i;
    for (i = 0; i < TX_CHANS; ++i)
      count += sprintf (page, " %u/%u",
			query_tx_channel_config (dev, i, BUCKET_FULLNESS_ACCESS),
			query_tx_channel_config (dev, i, BUCKET_CAPACITY_ACCESS));
    count += sprintf (page+count, ".\n");
    return count;
  }
#endif
  
  if (!left--)
    return sprintf (page,
		    "cells: TX %lu, RX %lu, HEC errors %lu, unassigned %lu.\n",
		    dev->tx_cell_count, dev->rx_cell_count,
		    dev->hec_error_count, dev->unassigned_cell_count);
  
  if (!left--)
    return sprintf (page,
		    "free cell buffers: TX %hu, RX %hu+%hu.\n",
		    rd_regw (dev, TX_FREE_BUFFER_COUNT_OFF),
		    rd_regw (dev, RX_FREE_BUFFER_COUNT_OFF),
		    dev->noof_spare_buffers);
  
  if (!left--)
    return sprintf (page,
		    "cps remaining: TX %u, RX %u\n",
		    dev->tx_avail, dev->rx_avail);
  
  return 0;
}