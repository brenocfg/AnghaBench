#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ state; } ;
struct perf_event {TYPE_3__ hw; } ;
struct cpu_hw_events {TYPE_2__* ds; } ;
struct TYPE_4__ {int /*<<< orphan*/  bts_interrupt_threshold; int /*<<< orphan*/  bts_absolute_maximum; int /*<<< orphan*/  bts_buffer_base; } ;
struct bts_ctx {int /*<<< orphan*/  handle; TYPE_1__ ds_back; } ;
struct bts_buffer {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  bts_interrupt_threshold; int /*<<< orphan*/  bts_absolute_maximum; int /*<<< orphan*/  bts_buffer_base; } ;

/* Variables and functions */
 scalar_t__ PERF_HES_STOPPED ; 
 int /*<<< orphan*/  __bts_event_start (struct perf_event*) ; 
 scalar_t__ bts_buffer_reset (struct bts_buffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bts_ctx ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 struct bts_buffer* perf_aux_output_begin (int /*<<< orphan*/ *,struct perf_event*) ; 
 int /*<<< orphan*/  perf_aux_output_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_itrace_started (struct perf_event*) ; 
 void* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bts_event_start(struct perf_event *event, int flags)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct bts_ctx *bts = this_cpu_ptr(&bts_ctx);
	struct bts_buffer *buf;

	buf = perf_aux_output_begin(&bts->handle, event);
	if (!buf)
		goto fail_stop;

	if (bts_buffer_reset(buf, &bts->handle))
		goto fail_end_stop;

	bts->ds_back.bts_buffer_base = cpuc->ds->bts_buffer_base;
	bts->ds_back.bts_absolute_maximum = cpuc->ds->bts_absolute_maximum;
	bts->ds_back.bts_interrupt_threshold = cpuc->ds->bts_interrupt_threshold;

	perf_event_itrace_started(event);
	event->hw.state = 0;

	__bts_event_start(event);

	return;

fail_end_stop:
	perf_aux_output_end(&bts->handle, 0);

fail_stop:
	event->hw.state = PERF_HES_STOPPED;
}