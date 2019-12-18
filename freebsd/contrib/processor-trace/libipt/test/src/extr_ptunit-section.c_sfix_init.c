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
struct section_fixture {int /*<<< orphan*/  thrd; int /*<<< orphan*/ * name; int /*<<< orphan*/ * file; int /*<<< orphan*/ * section; } ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ptunit_mkfile (int /*<<< orphan*/ **,int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  ptunit_thrd_init ; 

__attribute__((used)) static struct ptunit_result sfix_init(struct section_fixture *sfix)
{
	int errcode;

	sfix->section = NULL;
	sfix->file = NULL;
	sfix->name = NULL;

	errcode = ptunit_mkfile(&sfix->file, &sfix->name, "wb");
	ptu_int_eq(errcode, 0);

	ptu_test(ptunit_thrd_init, &sfix->thrd);

	return ptu_passed();
}