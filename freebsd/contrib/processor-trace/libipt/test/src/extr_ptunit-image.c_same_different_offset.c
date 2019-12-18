#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct ptunit_result {int dummy; } ;
struct image_fixture {int /*<<< orphan*/ * asid; int /*<<< orphan*/  image; TYPE_2__* section; TYPE_1__* mapping; } ;
struct TYPE_4__ {int size; scalar_t__ offset; int /*<<< orphan*/  filename; } ;
struct TYPE_3__ {int size; int* content; } ;

/* Variables and functions */
 int ifix_add_section (struct image_fixture*,int /*<<< orphan*/ ) ; 
 int pt_image_add (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int pt_image_read (int /*<<< orphan*/ *,int*,int*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 int /*<<< orphan*/  ptu_int_gt (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int,int) ; 

__attribute__((used)) static struct ptunit_result same_different_offset(struct image_fixture *ifix)
{
	uint8_t buffer[] = { 0xcc, 0xcc }, i;
	int status, isid, index;

	/* Add another section from a different part of the same file as an
	 * existing section.
	 */
	index = ifix_add_section(ifix, ifix->section[0].filename);
	ptu_int_gt(index, 0);

	ifix->section[index].offset = ifix->section[0].offset + 0x10;
	ptu_uint_eq(ifix->section[index].size, ifix->section[0].size);

	/* Change the content of the new section so we can distinguish them. */
	for (i = 0; i < ifix->mapping[index].size; ++i)
		ifix->mapping[index].content[i] += 0x10;


	status = pt_image_add(&ifix->image, &ifix->section[0], &ifix->asid[0],
			      0x1000ull, 0);
	ptu_int_eq(status, 0);

	status = pt_image_add(&ifix->image, &ifix->section[index],
			      &ifix->asid[0], 0x1000ull, 0);
	ptu_int_eq(status, 0);

	isid = -1;
	status = pt_image_read(&ifix->image, &isid, buffer, 1, &ifix->asid[0],
			       0x1000ull);
	ptu_int_eq(status, 1);
	ptu_int_eq(isid, 0);
	ptu_uint_eq(buffer[0], 0x10);
	ptu_uint_eq(buffer[1], 0xcc);

	isid = -1;
	status = pt_image_read(&ifix->image, &isid, buffer, 1, &ifix->asid[0],
			       0x100full);
	ptu_int_eq(status, 1);
	ptu_int_eq(isid, 0);
	ptu_uint_eq(buffer[0], 0x1f);
	ptu_uint_eq(buffer[1], 0xcc);

	return ptu_passed();
}