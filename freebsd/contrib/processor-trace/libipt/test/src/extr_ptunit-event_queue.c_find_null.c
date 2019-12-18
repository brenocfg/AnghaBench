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
typedef  enum pt_event_type { ____Placeholder_pt_event_type } pt_event_type ;
typedef  enum pt_event_binding { ____Placeholder_pt_event_binding } pt_event_binding ;

/* Variables and functions */
 struct pt_event* pt_evq_find (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ptu_null (struct pt_event*) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result find_null(enum pt_event_binding evb,
				      enum pt_event_type evt)
{
	struct pt_event *ev;

	ev = pt_evq_find(NULL, evb, evt);
	ptu_null(ev);

	return ptu_passed();
}