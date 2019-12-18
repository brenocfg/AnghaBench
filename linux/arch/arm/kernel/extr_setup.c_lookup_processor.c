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
typedef  int /*<<< orphan*/  u32 ;
struct proc_info_list {int dummy; } ;

/* Variables and functions */
 struct proc_info_list* lookup_processor_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

struct proc_info_list *lookup_processor(u32 midr)
{
	struct proc_info_list *list = lookup_processor_type(midr);

	if (!list) {
		pr_err("CPU%u: configuration botched (ID %08x), CPU halted\n",
		       smp_processor_id(), midr);
		while (1)
		/* can't use cpu_relax() here as it may require MMU setup */;
	}

	return list;
}