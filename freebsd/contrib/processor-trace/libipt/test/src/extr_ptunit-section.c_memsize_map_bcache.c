#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct section_fixture {TYPE_1__* section; int /*<<< orphan*/  name; } ;
struct ptunit_result {int dummy; } ;
struct pt_bcache_entry {int dummy; } ;
struct TYPE_7__ {int size; } ;

/* Variables and functions */
 int pt_mk_section (TYPE_1__**,int /*<<< orphan*/ ,int,int) ; 
 int pt_section_alloc_bcache (TYPE_1__*) ; 
 int pt_section_map (TYPE_1__*) ; 
 int pt_section_memsize (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int pt_section_unmap (TYPE_1__*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  ptu_uint_ge (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sfix_write (struct section_fixture*,int*) ; 

__attribute__((used)) static struct ptunit_result memsize_map_bcache(struct section_fixture *sfix)
{
	uint64_t memsize;
	uint8_t bytes[] = { 0xcc, 0x2, 0x4, 0x6 };
	int errcode;

	sfix_write(sfix, bytes);

	errcode = pt_mk_section(&sfix->section, sfix->name, 0x1ull, 0x3ull);
	ptu_int_eq(errcode, 0);
	ptu_ptr(sfix->section);

	errcode = pt_section_map(sfix->section);
	ptu_int_eq(errcode, 0);

	errcode = pt_section_alloc_bcache(sfix->section);
	ptu_int_eq(errcode, 0);

	errcode = pt_section_memsize(sfix->section, &memsize);
	ptu_int_eq(errcode, 0);
	ptu_uint_ge(memsize,
		    sfix->section->size * sizeof(struct pt_bcache_entry));

	errcode = pt_section_unmap(sfix->section);
	ptu_int_eq(errcode, 0);

	return ptu_passed();
}