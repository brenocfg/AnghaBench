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
struct section_fixture {int /*<<< orphan*/  name; int /*<<< orphan*/  section; } ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 int pt_mk_section (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pte_invalid ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result create_bad_offset(struct section_fixture *sfix)
{
	int errcode;

	errcode = pt_mk_section(&sfix->section, sfix->name, 0x10ull, 0x0ull);
	ptu_int_eq(errcode, -pte_invalid);

	return ptu_passed();
}