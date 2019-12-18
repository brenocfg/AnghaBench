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
typedef  enum pt_event_type { ____Placeholder_pt_event_type } pt_event_type ;
typedef  enum pt_event_binding { ____Placeholder_pt_event_binding } pt_event_binding ;

/* Variables and functions */
 int /*<<< orphan*/  evq_enqueue_other ; 
 struct pt_event* pt_evq_find (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ptu_null (struct pt_event*) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,struct evq_fixture*,int,int,size_t) ; 

__attribute__((used)) static struct ptunit_result find_none_evt(struct evq_fixture *efix,
					  enum pt_event_binding evb,
					  enum pt_event_type evt,
					  size_t num)
{
	struct pt_event *ev;

	ptu_test(evq_enqueue_other, efix, evb, evt, num);

	ev = pt_evq_find(&efix->evq, evb, evt);
	ptu_null(ev);

	return ptu_passed();
}