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
 int /*<<< orphan*/  evq_empty ; 
 int evq_max ; 
 int /*<<< orphan*/  evq_others_empty ; 
 int /*<<< orphan*/  evq_pending ; 
 struct pt_event* pt_evq_dequeue (int /*<<< orphan*/ *,int) ; 
 struct pt_event* pt_evq_enqueue (int /*<<< orphan*/ *,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (struct pt_event*) ; 
 int /*<<< orphan*/  ptu_ptr_eq (struct pt_event*,struct pt_event*) ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,struct evq_fixture*,int) ; 
 int /*<<< orphan*/  ptu_uint_le (size_t,int) ; 

__attribute__((used)) static struct ptunit_result enqueue_all_dequeue(struct evq_fixture *efix,
						enum pt_event_binding evb,
						size_t num)
{
	struct pt_event *in[evq_max], *out[evq_max];
	size_t idx;

	ptu_uint_le(num, evq_max - 2);

	for (idx = 0; idx < num; ++idx) {
		in[idx] = pt_evq_enqueue(&efix->evq, evb);
		ptu_ptr(in[idx]);
	}

	ptu_test(evq_pending, efix, evb);
	ptu_test(evq_others_empty, efix, evb);

	for (idx = 0; idx < num; ++idx) {
		out[idx] = pt_evq_dequeue(&efix->evq, evb);
		ptu_ptr_eq(out[idx], in[idx]);
	}

	ptu_test(evq_empty, efix, evb);

	return ptu_passed();
}