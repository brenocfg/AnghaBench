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
struct pmu {int dummy; } ;
struct hv_24x7_request_buffer {int dummy; } ;
struct hv_24x7_data_result_buffer {int dummy; } ;

/* Variables and functions */
 unsigned int PERF_PMU_TXN_READ ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_24x7_reqb ; 
 int /*<<< orphan*/  hv_24x7_resb ; 
 int /*<<< orphan*/  hv_24x7_txn_flags ; 
 int /*<<< orphan*/  init_24x7_request (struct hv_24x7_request_buffer*,struct hv_24x7_data_result_buffer*) ; 
 int /*<<< orphan*/  put_cpu_var (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void h_24x7_event_start_txn(struct pmu *pmu, unsigned int flags)
{
	struct hv_24x7_request_buffer *request_buffer;
	struct hv_24x7_data_result_buffer *result_buffer;

	/* We should not be called if we are already in a txn */
	WARN_ON_ONCE(__this_cpu_read(hv_24x7_txn_flags));

	__this_cpu_write(hv_24x7_txn_flags, flags);
	if (flags & ~PERF_PMU_TXN_READ)
		return;

	request_buffer = (void *)get_cpu_var(hv_24x7_reqb);
	result_buffer = (void *)get_cpu_var(hv_24x7_resb);

	init_24x7_request(request_buffer, result_buffer);

	put_cpu_var(hv_24x7_resb);
	put_cpu_var(hv_24x7_reqb);
}