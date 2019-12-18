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
typedef  int u64 ;
struct hv_guest_mapping_flush_list {int address_space; scalar_t__ flags; } ;
typedef  int (* hyperv_fill_flush_list_func ) (struct hv_guest_mapping_flush_list*,void*) ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  HVCALL_FLUSH_GUEST_PHYSICAL_ADDRESS_LIST ; 
 int HV_HYPERCALL_RESULT_MASK ; 
 int hv_do_rep_hypercall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct hv_guest_mapping_flush_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hv_hypercall_pg ; 
 int /*<<< orphan*/  hyperv_pcpu_input_arg ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hyperv_nested_flush_guest_mapping_range (int,int) ; 
 scalar_t__ unlikely (int) ; 

int hyperv_flush_guest_mapping_range(u64 as,
		hyperv_fill_flush_list_func fill_flush_list_func, void *data)
{
	struct hv_guest_mapping_flush_list **flush_pcpu;
	struct hv_guest_mapping_flush_list *flush;
	u64 status = 0;
	unsigned long flags;
	int ret = -ENOTSUPP;
	int gpa_n = 0;

	if (!hv_hypercall_pg || !fill_flush_list_func)
		goto fault;

	local_irq_save(flags);

	flush_pcpu = (struct hv_guest_mapping_flush_list **)
		this_cpu_ptr(hyperv_pcpu_input_arg);

	flush = *flush_pcpu;
	if (unlikely(!flush)) {
		local_irq_restore(flags);
		goto fault;
	}

	flush->address_space = as;
	flush->flags = 0;

	gpa_n = fill_flush_list_func(flush, data);
	if (gpa_n < 0) {
		local_irq_restore(flags);
		goto fault;
	}

	status = hv_do_rep_hypercall(HVCALL_FLUSH_GUEST_PHYSICAL_ADDRESS_LIST,
				     gpa_n, 0, flush, NULL);

	local_irq_restore(flags);

	if (!(status & HV_HYPERCALL_RESULT_MASK))
		ret = 0;
	else
		ret = status;
fault:
	trace_hyperv_nested_flush_guest_mapping_range(as, ret);
	return ret;
}