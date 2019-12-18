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
struct pt_event {int type; } ;
struct evq_fixture {int /*<<< orphan*/  evq; } ;
typedef  enum pt_event_type { ____Placeholder_pt_event_type } pt_event_type ;
typedef  enum pt_event_binding { ____Placeholder_pt_event_binding } pt_event_binding ;

/* Variables and functions */
 struct pt_event* pt_evq_enqueue (int /*<<< orphan*/ *,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (struct pt_event*) ; 

__attribute__((used)) static struct ptunit_result evq_enqueue_other(struct evq_fixture *efix,
					      enum pt_event_binding evb,
					      enum pt_event_type evt,
					      size_t num)
{
	enum pt_event_type ot;
	struct pt_event *ev;
	size_t other;

	for (other = 0; other < num; ++other) {
		ot = (enum pt_event_type) other;
		if (ot != evt) {
			ev = pt_evq_enqueue(&efix->evq, evb);
			ptu_ptr(ev);

			ev->type = ot;
		}
	}

	return ptu_passed();
}