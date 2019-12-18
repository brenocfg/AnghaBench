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
 size_t evb_max ; 
 struct pt_event* pt_evq_enqueue (int /*<<< orphan*/ *,int) ; 
 struct pt_event* pt_evq_find (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ptu_null (struct pt_event*) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (struct pt_event*) ; 

__attribute__((used)) static struct ptunit_result find_none_evb(struct evq_fixture *efix,
					  enum pt_event_binding evb,
					  enum pt_event_type evt)
{
	struct pt_event *ev;
	size_t other;

	for (other = 0; other < evb_max; ++other) {
		enum pt_event_binding ob;

		ob = (enum pt_event_binding) other;
		if (ob != evb) {
			ev = pt_evq_enqueue(&efix->evq, ob);
			ptu_ptr(ev);

			ev->type = evt;
		}
	}

	ev = pt_evq_find(&efix->evq, evb, evt);
	ptu_null(ev);

	return ptu_passed();
}