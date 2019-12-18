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
struct topa {int last; scalar_t__ size; scalar_t__ offset; int /*<<< orphan*/  list; } ;
struct pt_buffer {struct topa* last; struct topa* cur; struct topa* first; int /*<<< orphan*/  tables; } ;
struct TYPE_2__ {int end; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PT_CAP_topa_multiple_entries ; 
 int TENTS_PER_PAGE ; 
 TYPE_1__* TOPA_ENTRY (struct topa*,int) ; 
 int /*<<< orphan*/  intel_pt_validate_hw_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  topa_pfn (struct topa*) ; 

__attribute__((used)) static void topa_insert_table(struct pt_buffer *buf, struct topa *topa)
{
	struct topa *last = buf->last;

	list_add_tail(&topa->list, &buf->tables);

	if (!buf->first) {
		buf->first = buf->last = buf->cur = topa;
		return;
	}

	topa->offset = last->offset + last->size;
	buf->last = topa;

	if (!intel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries))
		return;

	BUG_ON(last->last != TENTS_PER_PAGE - 1);

	TOPA_ENTRY(last, -1)->base = topa_pfn(topa);
	TOPA_ENTRY(last, -1)->end = 1;
}