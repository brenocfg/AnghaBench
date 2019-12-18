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
 int pt_evq_empty (int /*<<< orphan*/ *,int) ; 
 int pt_evq_pending (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_int_gt (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result evq_empty(struct evq_fixture *efix,
				      enum pt_event_binding evb)
{
	int status;

	status = pt_evq_empty(&efix->evq, evb);
	ptu_int_gt(status, 0);

	status = pt_evq_pending(&efix->evq, evb);
	ptu_int_eq(status, 0);

	return ptu_passed();
}