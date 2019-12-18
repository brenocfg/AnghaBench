#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct section_fixture {TYPE_1__* section; int /*<<< orphan*/  name; } ;
struct ptunit_result {int dummy; } ;
struct TYPE_4__ {scalar_t__ mcount; } ;

/* Variables and functions */
 scalar_t__ UINT16_MAX ; 
 int pt_mk_section (TYPE_1__**,int /*<<< orphan*/ ,int,int) ; 
 int pt_section_map (TYPE_1__*) ; 
 int /*<<< orphan*/  pte_overflow ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  sfix_write (struct section_fixture*,int*) ; 

__attribute__((used)) static struct ptunit_result map_overflow(struct section_fixture *sfix)
{
	uint8_t bytes[] = { 0xcc, 0x2, 0x4, 0x6 };
	int errcode;

	sfix_write(sfix, bytes);

	errcode = pt_mk_section(&sfix->section, sfix->name, 0x1ull, 0x3ull);
	ptu_int_eq(errcode, 0);
	ptu_ptr(sfix->section);

	sfix->section->mcount = UINT16_MAX;

	errcode = pt_section_map(sfix->section);
	ptu_int_eq(errcode, -pte_overflow);

	sfix->section->mcount = 0;

	return ptu_passed();
}