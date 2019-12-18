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
typedef  int /*<<< orphan*/  uint64_t ;
struct section_fixture {int /*<<< orphan*/  section; int /*<<< orphan*/  name; } ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 int pt_mk_section (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 char* pt_section_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_section_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_section_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_str_eq (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sfix_write (struct section_fixture*,int*) ; 

__attribute__((used)) static struct ptunit_result create(struct section_fixture *sfix)
{
	const char *name;
	uint8_t bytes[] = { 0xcc, 0xcc, 0xcc, 0xcc, 0xcc };
	uint64_t offset, size;
	int errcode;

	sfix_write(sfix, bytes);

	errcode = pt_mk_section(&sfix->section, sfix->name, 0x1ull, 0x3ull);
	ptu_int_eq(errcode, 0);
	ptu_ptr(sfix->section);

	name = pt_section_filename(sfix->section);
	ptu_str_eq(name, sfix->name);

	offset = pt_section_offset(sfix->section);
	ptu_uint_eq(offset, 0x1ull);

	size = pt_section_size(sfix->section);
	ptu_uint_eq(size, 0x3ull);

	return ptu_passed();
}