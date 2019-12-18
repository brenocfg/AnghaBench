#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * section; } ;
struct test_fixture {int /*<<< orphan*/  section; TYPE_1__ image; } ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfix_init ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,struct test_fixture*) ; 

__attribute__((used)) static struct ptunit_result cifix_init(struct test_fixture *tfix)
{
	ptu_test(cfix_init, tfix);

	tfix->image.section = &tfix->section;

	return ptu_passed();
}