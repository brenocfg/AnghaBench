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
struct TYPE_2__ {struct dbg_bus_block_data* blocks; } ;
struct dbg_tools_data {TYPE_1__ bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
struct dbg_bus_line {int dummy; } ;
struct dbg_bus_block_data {int line_num; } ;
struct dbg_bus_block {size_t lines_offset; scalar_t__ has_latency_events; } ;
typedef  enum block_id { ____Placeholder_block_id } block_id ;

/* Variables and functions */
 int NUM_DBG_LINES (struct dbg_bus_block*) ; 
 size_t NUM_EXTRA_DBG_LINES (struct dbg_bus_block*) ; 
 struct dbg_bus_line* OSAL_NULL ; 
 int /*<<< orphan*/ * dbg_bus_lines ; 
 struct dbg_bus_block* get_dbg_bus_block_desc (struct ecore_hwfn*,int) ; 

__attribute__((used)) static struct dbg_bus_line* get_dbg_bus_line_desc(struct ecore_hwfn *p_hwfn,
														enum block_id block_id)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	struct dbg_bus_block_data *block_bus;
	struct dbg_bus_block *block_desc;

	block_bus = &dev_data->bus.blocks[block_id];
	block_desc = get_dbg_bus_block_desc(p_hwfn, block_id);

	if (!block_bus->line_num ||
		(block_bus->line_num == 1 && block_desc->has_latency_events) ||
		block_bus->line_num >= NUM_DBG_LINES(block_desc))
		return OSAL_NULL;

	return (struct dbg_bus_line *)&dbg_bus_lines[block_desc->lines_offset + block_bus->line_num - NUM_EXTRA_DBG_LINES(block_desc)];
}