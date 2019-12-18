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
struct so_list {TYPE_1__* lm_info; struct section_table* sections; } ;
struct section_table {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  base_address; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  adjust_section_address (struct section_table*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
kld_relocate_section_addresses (struct so_list *so, struct section_table *sec)
{
	static CORE_ADDR curr_addr;

	if (sec == so->sections)
		curr_addr = so->lm_info->base_address;

	adjust_section_address(sec, &curr_addr);
}