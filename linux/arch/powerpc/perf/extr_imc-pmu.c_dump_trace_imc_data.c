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
typedef  int /*<<< orphan*/  u64 ;
struct trace_imc_data {int dummy; } ;
struct perf_sample_data {int dummy; } ;
struct perf_output_handle {int dummy; } ;
struct perf_event_header {int /*<<< orphan*/  size; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 scalar_t__ get_trace_imc_event_base_addr () ; 
 scalar_t__ perf_output_begin (struct perf_output_handle*,struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_output_end (struct perf_output_handle*) ; 
 int /*<<< orphan*/  perf_output_sample (struct perf_output_handle*,struct perf_event_header*,struct perf_sample_data*,struct perf_event*) ; 
 int trace_imc_mem_size ; 
 int trace_imc_prepare_sample (struct trace_imc_data*,struct perf_sample_data*,int /*<<< orphan*/ *,struct perf_event_header*,struct perf_event*) ; 

__attribute__((used)) static void dump_trace_imc_data(struct perf_event *event)
{
	struct trace_imc_data *mem;
	int i, ret;
	u64 prev_tb = 0;

	mem = (struct trace_imc_data *)get_trace_imc_event_base_addr();
	for (i = 0; i < (trace_imc_mem_size / sizeof(struct trace_imc_data));
		i++, mem++) {
		struct perf_sample_data data;
		struct perf_event_header header;

		ret = trace_imc_prepare_sample(mem, &data, &prev_tb, &header, event);
		if (ret) /* Exit, if not a valid record */
			break;
		else {
			/* If this is a valid record, create the sample */
			struct perf_output_handle handle;

			if (perf_output_begin(&handle, event, header.size))
				return;

			perf_output_sample(&handle, &header, &data, event);
			perf_output_end(&handle);
		}
	}
}