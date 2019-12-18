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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdt_entries; int /*<<< orphan*/  pdt_size; } ;

/* Variables and functions */
 scalar_t__ PDT_NONE ; 
 TYPE_1__ pdt_status ; 
 scalar_t__ pdt_type ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

void arch_report_meminfo(struct seq_file *m)
{
	if (pdt_type == PDT_NONE)
		return;

	seq_printf(m, "PDT_max_entries: %7lu\n",
			pdt_status.pdt_size);
	seq_printf(m, "PDT_cur_entries: %7lu\n",
			pdt_status.pdt_entries);
}