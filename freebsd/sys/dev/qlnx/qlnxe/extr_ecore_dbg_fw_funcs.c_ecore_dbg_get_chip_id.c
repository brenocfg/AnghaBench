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
struct dbg_tools_data {int /*<<< orphan*/  chip_id; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
typedef  enum chip_ids { ____Placeholder_chip_ids } chip_ids ;

/* Variables and functions */

enum chip_ids ecore_dbg_get_chip_id(struct ecore_hwfn *p_hwfn)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;

	return (enum chip_ids)dev_data->chip_id;
}