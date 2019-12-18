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
struct topa {int dummy; } ;
struct pt_buffer {unsigned long nr_pages; int /*<<< orphan*/  last; int /*<<< orphan*/  first; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int end; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PT_CAP_topa_multiple_entries ; 
 TYPE_1__* TOPA_ENTRY (int /*<<< orphan*/ ,int) ; 
 scalar_t__ intel_pt_validate_hw_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_buffer_fini_topa (struct pt_buffer*) ; 
 int /*<<< orphan*/  pt_topa_dump (struct pt_buffer*) ; 
 struct topa* topa_alloc (int,int /*<<< orphan*/ ) ; 
 int topa_insert_pages (struct pt_buffer*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  topa_insert_table (struct pt_buffer*,struct topa*) ; 
 int /*<<< orphan*/  topa_pfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pt_buffer_init_topa(struct pt_buffer *buf, int cpu,
			       unsigned long nr_pages, gfp_t gfp)
{
	struct topa *topa;
	int err;

	topa = topa_alloc(cpu, gfp);
	if (!topa)
		return -ENOMEM;

	topa_insert_table(buf, topa);

	while (buf->nr_pages < nr_pages) {
		err = topa_insert_pages(buf, cpu, gfp);
		if (err) {
			pt_buffer_fini_topa(buf);
			return -ENOMEM;
		}
	}

	/* link last table to the first one, unless we're double buffering */
	if (intel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries)) {
		TOPA_ENTRY(buf->last, -1)->base = topa_pfn(buf->first);
		TOPA_ENTRY(buf->last, -1)->end = 1;
	}

	pt_topa_dump(buf);
	return 0;
}