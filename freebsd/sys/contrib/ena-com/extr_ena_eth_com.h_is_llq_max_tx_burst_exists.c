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
struct TYPE_2__ {scalar_t__ max_entries_in_tx_burst; } ;
struct ena_com_io_sq {scalar_t__ mem_queue_type; TYPE_1__ llq_info; } ;

/* Variables and functions */
 scalar_t__ ENA_ADMIN_PLACEMENT_POLICY_DEV ; 

__attribute__((used)) static inline bool is_llq_max_tx_burst_exists(struct ena_com_io_sq *io_sq)
{
	return (io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV) &&
	       io_sq->llq_info.max_entries_in_tx_burst > 0;
}