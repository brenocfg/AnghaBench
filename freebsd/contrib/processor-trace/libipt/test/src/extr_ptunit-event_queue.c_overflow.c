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
 int evq_max ; 
 struct pt_event* pt_evq_dequeue (int /*<<< orphan*/ *,int) ; 
 struct pt_event* pt_evq_enqueue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptu_null (struct pt_event*) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (struct pt_event*) ; 
 int /*<<< orphan*/  ptu_ptr_eq (struct pt_event*,struct pt_event*) ; 
 int /*<<< orphan*/  ptu_uint_le (size_t,int) ; 

__attribute__((used)) static struct ptunit_result overflow(struct evq_fixture *efix,
				     enum pt_event_binding evb,
				     size_t num)
{
	struct pt_event *in[evq_max], *out[evq_max], *ev;
	size_t idx;

	ptu_uint_le(num, evq_max - 2);

	for (idx = 0; idx < (evq_max - 2); ++idx) {
		in[idx] = pt_evq_enqueue(&efix->evq, evb);
		ptu_ptr(in[idx]);
	}

	for (idx = 0; idx < num; ++idx) {
		ev = pt_evq_enqueue(&efix->evq, evb);
		ptu_null(ev);
	}

	for (idx = 0; idx < num; ++idx) {
		out[idx] = pt_evq_dequeue(&efix->evq, evb);
		ptu_ptr_eq(out[idx], in[idx]);
	}

	return ptu_passed();
}