#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ucount; int mcount; } ;
struct TYPE_4__ {TYPE_3__* section; } ;
struct TYPE_5__ {TYPE_1__ msec; } ;
struct test_fixture {TYPE_3__ section; TYPE_2__ mcache; } ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,struct test_fixture*) ; 
 int /*<<< orphan*/  sfix_init ; 

__attribute__((used)) static struct ptunit_result cfix_init(struct test_fixture *tfix)
{
	ptu_test(sfix_init, tfix);

	tfix->mcache.msec.section = &tfix->section;

	tfix->section.ucount = 1;
	tfix->section.mcount = 1;

	return ptu_passed();
}