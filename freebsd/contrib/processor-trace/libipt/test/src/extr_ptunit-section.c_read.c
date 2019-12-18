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

/* Variables and functions */
 int pt_mk_section (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int pt_section_map (int /*<<< orphan*/ ) ; 
 int pt_section_read (int /*<<< orphan*/ ,int*,int,int) ; 
 int pt_section_unmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_uint_eq (int,int) ; 
 int /*<<< orphan*/  sfix_write (struct section_fixture*,int*) ; 

__attribute__((used)) static struct ptunit_result read(struct section_fixture *sfix)
{
	uint8_t bytes[] = { 0xcc, 0x2, 0x4, 0x6 };
	uint8_t buffer[] = { 0xcc, 0xcc, 0xcc };
	int status;

	sfix_write(sfix, bytes);

	status = pt_mk_section(&sfix->section, sfix->name, 0x1ull, 0x3ull);
	ptu_int_eq(status, 0);
	ptu_ptr(sfix->section);

	status = pt_section_map(sfix->section);
	ptu_int_eq(status, 0);

	status = pt_section_read(sfix->section, buffer, 2, 0x0ull);
	ptu_int_eq(status, 2);
	ptu_uint_eq(buffer[0], bytes[1]);
	ptu_uint_eq(buffer[1], bytes[2]);
	ptu_uint_eq(buffer[2], 0xcc);

	status = pt_section_unmap(sfix->section);
	ptu_int_eq(status, 0);

	return ptu_passed();
}