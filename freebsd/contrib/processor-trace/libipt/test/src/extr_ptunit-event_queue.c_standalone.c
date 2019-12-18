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
struct pt_event {int /*<<< orphan*/  status_update; int /*<<< orphan*/  ip_suppressed; } ;
struct evq_fixture {int /*<<< orphan*/  evq; } ;

/* Variables and functions */
 struct pt_event* pt_evq_standalone (int /*<<< orphan*/ *) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (struct pt_event*) ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static struct ptunit_result standalone(struct evq_fixture *efix)
{
	struct pt_event *ev;

	ev = pt_evq_standalone(&efix->evq);
	ptu_ptr(ev);
	ptu_uint_eq(ev->ip_suppressed, 0ul);
	ptu_uint_eq(ev->status_update, 0ul);

	return ptu_passed();
}