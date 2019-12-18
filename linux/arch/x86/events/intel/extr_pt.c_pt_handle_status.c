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
struct pt_buffer {scalar_t__ output_off; int /*<<< orphan*/  snapshot; } ;
struct pt {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_RTIT_STATUS ; 
 int /*<<< orphan*/  PERF_AUX_FLAG_TRUNCATED ; 
 int /*<<< orphan*/  PT_CAP_topa_multiple_entries ; 
 int RTIT_STATUS_ERROR ; 
 int RTIT_STATUS_STOPPED ; 
 scalar_t__ TOPA_PMI_MARGIN ; 
 int /*<<< orphan*/  intel_pt_validate_hw_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  perf_aux_output_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pt_buffer* perf_get_aux (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*) ; 
 int /*<<< orphan*/  pt_buffer_advance (struct pt_buffer*) ; 
 void* pt_buffer_region (struct pt_buffer*) ; 
 scalar_t__ pt_buffer_region_size (struct pt_buffer*) ; 
 int /*<<< orphan*/  pt_topa_dump (struct pt_buffer*) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pt_handle_status(struct pt *pt)
{
	struct pt_buffer *buf = perf_get_aux(&pt->handle);
	int advance = 0;
	u64 status;

	rdmsrl(MSR_IA32_RTIT_STATUS, status);

	if (status & RTIT_STATUS_ERROR) {
		pr_err_ratelimited("ToPA ERROR encountered, trying to recover\n");
		pt_topa_dump(buf);
		status &= ~RTIT_STATUS_ERROR;
	}

	if (status & RTIT_STATUS_STOPPED) {
		status &= ~RTIT_STATUS_STOPPED;

		/*
		 * On systems that only do single-entry ToPA, hitting STOP
		 * means we are already losing data; need to let the decoder
		 * know.
		 */
		if (!intel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries) ||
		    buf->output_off == pt_buffer_region_size(buf)) {
			perf_aux_output_flag(&pt->handle,
			                     PERF_AUX_FLAG_TRUNCATED);
			advance++;
		}
	}

	/*
	 * Also on single-entry ToPA implementations, interrupt will come
	 * before the output reaches its output region's boundary.
	 */
	if (!intel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries) &&
	    !buf->snapshot &&
	    pt_buffer_region_size(buf) - buf->output_off <= TOPA_PMI_MARGIN) {
		void *head = pt_buffer_region(buf);

		/* everything within this margin needs to be zeroed out */
		memset(head + buf->output_off, 0,
		       pt_buffer_region_size(buf) -
		       buf->output_off);
		advance++;
	}

	if (advance)
		pt_buffer_advance(buf);

	wrmsrl(MSR_IA32_RTIT_STATUS, status);
}