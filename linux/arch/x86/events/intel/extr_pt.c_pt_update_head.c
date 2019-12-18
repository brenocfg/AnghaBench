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
typedef  scalar_t__ u64 ;
struct pt_buffer {scalar_t__ output_off; scalar_t__ cur_idx; int nr_pages; int /*<<< orphan*/  data_size; int /*<<< orphan*/  head; scalar_t__ snapshot; TYPE_1__* cur; } ;
struct pt {int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {scalar_t__ offset; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ TOPA_ENTRY_SIZE (TYPE_1__*,scalar_t__) ; 
 int local64_xchg (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  local_add (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_set (int /*<<< orphan*/ *,scalar_t__) ; 
 struct pt_buffer* perf_get_aux (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pt_update_head(struct pt *pt)
{
	struct pt_buffer *buf = perf_get_aux(&pt->handle);
	u64 topa_idx, base, old;

	/* offset of the first region in this table from the beginning of buf */
	base = buf->cur->offset + buf->output_off;

	/* offset of the current output region within this table */
	for (topa_idx = 0; topa_idx < buf->cur_idx; topa_idx++)
		base += TOPA_ENTRY_SIZE(buf->cur, topa_idx);

	if (buf->snapshot) {
		local_set(&buf->data_size, base);
	} else {
		old = (local64_xchg(&buf->head, base) &
		       ((buf->nr_pages << PAGE_SHIFT) - 1));
		if (base < old)
			base += buf->nr_pages << PAGE_SHIFT;

		local_add(base - old, &buf->data_size);
	}
}