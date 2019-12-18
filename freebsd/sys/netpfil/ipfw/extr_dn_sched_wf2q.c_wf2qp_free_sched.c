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
struct wf2qp_si {int /*<<< orphan*/  idle_heap; int /*<<< orphan*/  ne_heap; int /*<<< orphan*/  sch_heap; } ;
struct dn_sch_inst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
wf2qp_free_sched(struct dn_sch_inst *_si)
{
	struct wf2qp_si *si = (struct wf2qp_si *)(_si + 1);

	heap_free(&si->sch_heap);
	heap_free(&si->ne_heap);
	heap_free(&si->idle_heap);

	return 0;
}