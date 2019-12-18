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
typedef  unsigned long u64 ;
struct page {int dummy; } ;
struct debug_store {unsigned long bts_buffer_base; unsigned long bts_index; unsigned long bts_absolute_maximum; unsigned long bts_interrupt_threshold; } ;
struct bts_phys {unsigned long size; scalar_t__ offset; unsigned long displacement; struct page* page; } ;
struct bts_buffer {size_t cur_buf; scalar_t__ end; int /*<<< orphan*/  snapshot; int /*<<< orphan*/  head; struct bts_phys* buf; } ;
struct TYPE_2__ {struct debug_store* ds; } ;

/* Variables and functions */
 unsigned long BTS_RECORD_SIZE ; 
 unsigned long BTS_SAFETY_MARGIN ; 
 scalar_t__ buf_size (struct page*) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 unsigned long local_read (int /*<<< orphan*/ *) ; 
 scalar_t__ page_address (struct page*) ; 
 TYPE_1__ per_cpu (int /*<<< orphan*/ ,int) ; 
 int raw_smp_processor_id () ; 

__attribute__((used)) static void
bts_config_buffer(struct bts_buffer *buf)
{
	int cpu = raw_smp_processor_id();
	struct debug_store *ds = per_cpu(cpu_hw_events, cpu).ds;
	struct bts_phys *phys = &buf->buf[buf->cur_buf];
	unsigned long index, thresh = 0, end = phys->size;
	struct page *page = phys->page;

	index = local_read(&buf->head);

	if (!buf->snapshot) {
		if (buf->end < phys->offset + buf_size(page))
			end = buf->end - phys->offset - phys->displacement;

		index -= phys->offset + phys->displacement;

		if (end - index > BTS_SAFETY_MARGIN)
			thresh = end - BTS_SAFETY_MARGIN;
		else if (end - index > BTS_RECORD_SIZE)
			thresh = end - BTS_RECORD_SIZE;
		else
			thresh = end;
	}

	ds->bts_buffer_base = (u64)(long)page_address(page) + phys->displacement;
	ds->bts_index = ds->bts_buffer_base + index;
	ds->bts_absolute_maximum = ds->bts_buffer_base + end;
	ds->bts_interrupt_threshold = !buf->snapshot
		? ds->bts_buffer_base + thresh
		: ds->bts_absolute_maximum + BTS_RECORD_SIZE;
}