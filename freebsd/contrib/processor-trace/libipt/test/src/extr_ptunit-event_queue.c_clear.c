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
struct evq_fixture {int /*<<< orphan*/  evq; } ;
typedef  enum pt_event_binding { ____Placeholder_pt_event_binding } pt_event_binding ;

/* Variables and functions */
 int /*<<< orphan*/  evq_empty ; 
 int pt_evq_clear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,struct evq_fixture*,int) ; 

__attribute__((used)) static struct ptunit_result clear(struct evq_fixture *efix,
				  enum pt_event_binding evb)
{
	int errcode;

	errcode = pt_evq_clear(&efix->evq, evb);
	ptu_int_eq(errcode, 0);

	ptu_test(evq_empty, efix, evb);

	return ptu_passed();
}