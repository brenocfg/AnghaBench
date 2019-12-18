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
struct ptunit_result {int dummy; } ;
struct pt_event {int dummy; } ;
struct evq_fixture {int /*<<< orphan*/  evq; } ;
typedef  enum pt_event_binding { ____Placeholder_pt_event_binding } pt_event_binding ;

/* Variables and functions */
 struct pt_event* pt_evq_dequeue (int /*<<< orphan*/ *,int) ; 
 struct pt_event* pt_evq_enqueue (int /*<<< orphan*/ *,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (struct pt_event*) ; 
 int /*<<< orphan*/  ptu_ptr_eq (struct pt_event*,struct pt_event*) ; 

__attribute__((used)) static struct ptunit_result enqueue_one_dequeue(struct evq_fixture *efix,
						enum pt_event_binding evb,
						size_t num)
{
	size_t idx;

	for (idx = 0; idx < num; ++idx) {
		struct pt_event *in, *out;

		in = pt_evq_enqueue(&efix->evq, evb);
		ptu_ptr(in);

		out = pt_evq_dequeue(&efix->evq, evb);
		ptu_ptr_eq(out, in);
	}

	return ptu_passed();
}