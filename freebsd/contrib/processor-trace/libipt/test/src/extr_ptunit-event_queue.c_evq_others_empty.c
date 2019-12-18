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
struct evq_fixture {int dummy; } ;
typedef  enum pt_event_binding { ____Placeholder_pt_event_binding } pt_event_binding ;

/* Variables and functions */
 int evb_max ; 
 int /*<<< orphan*/  evq_empty ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,struct evq_fixture*,int) ; 

__attribute__((used)) static struct ptunit_result evq_others_empty(struct evq_fixture *efix,
					     enum pt_event_binding evb)
{
	int other;

	for (other = 0; other < evb_max; ++other) {
		enum pt_event_binding ob;

		ob = (enum pt_event_binding) other;
		if (ob != evb)
			ptu_test(evq_empty, efix, ob);
	}

	return ptu_passed();
}