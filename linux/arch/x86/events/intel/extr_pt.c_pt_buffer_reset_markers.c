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
struct pt_buffer {scalar_t__ output_off; int nr_pages; unsigned long stop_pos; unsigned long intr_pos; TYPE_1__* intr_te; TYPE_1__* stop_te; int /*<<< orphan*/  head; } ;
struct perf_output_handle {unsigned long size; unsigned long wakeup; } ;
struct TYPE_2__ {int stop; int intr; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PERF_AUX_FLAG_TRUNCATED ; 
 int /*<<< orphan*/  PT_CAP_topa_multiple_entries ; 
 int /*<<< orphan*/  intel_pt_validate_hw_cap (int /*<<< orphan*/ ) ; 
 unsigned long local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  offset_in_page (unsigned long) ; 
 int /*<<< orphan*/  perf_aux_output_flag (struct perf_output_handle*,int /*<<< orphan*/ ) ; 
 scalar_t__ pt_buffer_region_size (struct pt_buffer*) ; 
 void* pt_topa_entry_for_page (struct pt_buffer*,unsigned long) ; 
 void* pt_topa_prev_entry (struct pt_buffer*,TYPE_1__*) ; 

__attribute__((used)) static int pt_buffer_reset_markers(struct pt_buffer *buf,
				   struct perf_output_handle *handle)

{
	unsigned long head = local64_read(&buf->head);
	unsigned long idx, npages, wakeup;

	/* can't stop in the middle of an output region */
	if (buf->output_off + handle->size + 1 < pt_buffer_region_size(buf)) {
		perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED);
		return -EINVAL;
	}


	/* single entry ToPA is handled by marking all regions STOP=1 INT=1 */
	if (!intel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries))
		return 0;

	/* clear STOP and INT from current entry */
	if (buf->stop_te) {
		buf->stop_te->stop = 0;
		buf->stop_te->intr = 0;
	}

	if (buf->intr_te)
		buf->intr_te->intr = 0;

	/* how many pages till the STOP marker */
	npages = handle->size >> PAGE_SHIFT;

	/* if it's on a page boundary, fill up one more page */
	if (!offset_in_page(head + handle->size + 1))
		npages++;

	idx = (head >> PAGE_SHIFT) + npages;
	idx &= buf->nr_pages - 1;

	if (idx != buf->stop_pos) {
		buf->stop_pos = idx;
		buf->stop_te = pt_topa_entry_for_page(buf, idx);
		buf->stop_te = pt_topa_prev_entry(buf, buf->stop_te);
	}

	wakeup = handle->wakeup >> PAGE_SHIFT;

	/* in the worst case, wake up the consumer one page before hard stop */
	idx = (head >> PAGE_SHIFT) + npages - 1;
	if (idx > wakeup)
		idx = wakeup;

	idx &= buf->nr_pages - 1;
	if (idx != buf->intr_pos) {
		buf->intr_pos = idx;
		buf->intr_te = pt_topa_entry_for_page(buf, idx);
		buf->intr_te = pt_topa_prev_entry(buf, buf->intr_te);
	}

	buf->stop_te->stop = 1;
	buf->stop_te->intr = 1;
	buf->intr_te->intr = 1;

	return 0;
}