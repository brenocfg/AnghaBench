#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pt_buffer {int /*<<< orphan*/  output_off; int /*<<< orphan*/  cur_idx; int /*<<< orphan*/  cur; int /*<<< orphan*/  snapshot; } ;
struct TYPE_6__ {int /*<<< orphan*/  head; } ;
struct pt {TYPE_2__ handle; int /*<<< orphan*/  handle_nmi; } ;
struct hw_perf_event {scalar_t__ state; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 scalar_t__ PERF_HES_STOPPED ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 struct pt_buffer* perf_aux_output_begin (TYPE_2__*,struct perf_event*) ; 
 int /*<<< orphan*/  perf_aux_output_end (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pt_buffer_reset_markers (struct pt_buffer*,TYPE_2__*) ; 
 int /*<<< orphan*/  pt_buffer_reset_offsets (struct pt_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_config (struct perf_event*) ; 
 int /*<<< orphan*/  pt_config_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_ctx ; 
 struct pt* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__* topa_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pt_event_start(struct perf_event *event, int mode)
{
	struct hw_perf_event *hwc = &event->hw;
	struct pt *pt = this_cpu_ptr(&pt_ctx);
	struct pt_buffer *buf;

	buf = perf_aux_output_begin(&pt->handle, event);
	if (!buf)
		goto fail_stop;

	pt_buffer_reset_offsets(buf, pt->handle.head);
	if (!buf->snapshot) {
		if (pt_buffer_reset_markers(buf, &pt->handle))
			goto fail_end_stop;
	}

	WRITE_ONCE(pt->handle_nmi, 1);
	hwc->state = 0;

	pt_config_buffer(topa_to_page(buf->cur)->table, buf->cur_idx,
			 buf->output_off);
	pt_config(event);

	return;

fail_end_stop:
	perf_aux_output_end(&pt->handle, 0);
fail_stop:
	hwc->state = PERF_HES_STOPPED;
}