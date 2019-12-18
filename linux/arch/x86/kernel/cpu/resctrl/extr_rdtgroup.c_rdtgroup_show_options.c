#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct kernfs_root {int dummy; } ;
struct TYPE_3__ {scalar_t__ alloc_enabled; } ;

/* Variables and functions */
 size_t RDT_RESOURCE_L2DATA ; 
 size_t RDT_RESOURCE_L3DATA ; 
 size_t RDT_RESOURCE_MBA ; 
 scalar_t__ is_mba_sc (TYPE_1__*) ; 
 TYPE_1__* rdt_resources_all ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int rdtgroup_show_options(struct seq_file *seq, struct kernfs_root *kf)
{
	if (rdt_resources_all[RDT_RESOURCE_L3DATA].alloc_enabled)
		seq_puts(seq, ",cdp");

	if (rdt_resources_all[RDT_RESOURCE_L2DATA].alloc_enabled)
		seq_puts(seq, ",cdpl2");

	if (is_mba_sc(&rdt_resources_all[RDT_RESOURCE_MBA]))
		seq_puts(seq, ",mba_MBps");

	return 0;
}