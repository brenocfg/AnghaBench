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
 int evb_max ; 
 struct pt_event* pt_evq_enqueue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pt_evq_init (int /*<<< orphan*/ *) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (struct pt_event*) ; 

__attribute__((used)) static struct ptunit_result efix_init_pending(struct evq_fixture *efix)
{
	struct pt_event *ev;
	int evb;

	pt_evq_init(&efix->evq);

	for (evb = 0; evb < evb_max; ++evb) {
		ev = pt_evq_enqueue(&efix->evq, (enum pt_event_binding) evb);
		ptu_ptr(ev);
	}

	return ptu_passed();
}