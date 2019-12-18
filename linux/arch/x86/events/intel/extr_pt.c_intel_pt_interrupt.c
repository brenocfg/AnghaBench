#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pt_buffer {int /*<<< orphan*/  output_off; int /*<<< orphan*/  cur_idx; int /*<<< orphan*/  cur; int /*<<< orphan*/  data_size; } ;
struct TYPE_9__ {int /*<<< orphan*/  head; struct perf_event* event; } ;
struct pt {TYPE_3__ handle; int /*<<< orphan*/  handle_nmi; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;
struct perf_event {TYPE_1__ hw; } ;
struct TYPE_8__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_HES_STOPPED ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pt_buffer* perf_aux_output_begin (TYPE_3__*,struct perf_event*) ; 
 int /*<<< orphan*/  perf_aux_output_end (TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct pt_buffer* perf_get_aux (TYPE_3__*) ; 
 int pt_buffer_reset_markers (struct pt_buffer*,TYPE_3__*) ; 
 int /*<<< orphan*/  pt_buffer_reset_offsets (struct pt_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_config (struct perf_event*) ; 
 int /*<<< orphan*/  pt_config_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_config_stop (struct perf_event*) ; 
 int /*<<< orphan*/  pt_ctx ; 
 int /*<<< orphan*/  pt_handle_status (struct pt*) ; 
 int /*<<< orphan*/  pt_read_offset (struct pt_buffer*) ; 
 int /*<<< orphan*/  pt_update_head (struct pt*) ; 
 struct pt* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_2__* topa_to_page (int /*<<< orphan*/ ) ; 

void intel_pt_interrupt(void)
{
	struct pt *pt = this_cpu_ptr(&pt_ctx);
	struct pt_buffer *buf;
	struct perf_event *event = pt->handle.event;

	/*
	 * There may be a dangling PT bit in the interrupt status register
	 * after PT has been disabled by pt_event_stop(). Make sure we don't
	 * do anything (particularly, re-enable) for this event here.
	 */
	if (!READ_ONCE(pt->handle_nmi))
		return;

	if (!event)
		return;

	pt_config_stop(event);

	buf = perf_get_aux(&pt->handle);
	if (!buf)
		return;

	pt_read_offset(buf);

	pt_handle_status(pt);

	pt_update_head(pt);

	perf_aux_output_end(&pt->handle, local_xchg(&buf->data_size, 0));

	if (!event->hw.state) {
		int ret;

		buf = perf_aux_output_begin(&pt->handle, event);
		if (!buf) {
			event->hw.state = PERF_HES_STOPPED;
			return;
		}

		pt_buffer_reset_offsets(buf, pt->handle.head);
		/* snapshot counters don't use PMI, so it's safe */
		ret = pt_buffer_reset_markers(buf, &pt->handle);
		if (ret) {
			perf_aux_output_end(&pt->handle, 0);
			return;
		}

		pt_config_buffer(topa_to_page(buf->cur)->table, buf->cur_idx,
				 buf->output_off);
		pt_config(event);
	}
}