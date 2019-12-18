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
typedef  int uint8_t ;
struct section_fixture {int /*<<< orphan*/  section; int /*<<< orphan*/  name; } ;
struct ptunit_result {int dummy; } ;
struct pt_image_section_cache {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int pt_mk_section (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int pt_section_attach (int /*<<< orphan*/ ,struct pt_image_section_cache*) ; 
 int pt_section_detach (int /*<<< orphan*/ ,struct pt_image_section_cache*) ; 
 int pt_section_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_eos ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfix_write (struct section_fixture*,int*) ; 

__attribute__((used)) static struct ptunit_result attach_bad_map(struct section_fixture *sfix)
{
	struct pt_image_section_cache iscache;
	uint8_t bytes[] = { 0xcc, 0x2, 0x4, 0x6 };
	int errcode;

	iscache.map = -pte_eos;

	sfix_write(sfix, bytes);

	errcode = pt_mk_section(&sfix->section, sfix->name, 0x1ull, 0x3ull);
	ptu_int_eq(errcode, 0);
	ptu_ptr(sfix->section);

	errcode = pt_section_attach(sfix->section, &iscache);
	ptu_int_eq(errcode, 0);

	errcode = pt_section_map(sfix->section);
	ptu_int_eq(errcode, -pte_eos);

	errcode = pt_section_detach(sfix->section, &iscache);
	ptu_int_eq(errcode, 0);

	return ptu_passed();
}