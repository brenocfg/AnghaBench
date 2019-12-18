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
struct TYPE_4__ {int size; } ;
struct TYPE_3__ {int size; } ;

/* Variables and functions */
 int pt_image_add (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int,int) ; 
 int pt_image_read (int /*<<< orphan*/ *,int*,int*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int,int) ; 

__attribute__((used)) static struct ptunit_result contained_back(struct image_fixture *ifix)
{
	uint8_t buffer[] = { 0xcc, 0xcc };
	int status, isid;

	ifix->section[0].size = 0x8;
	ifix->mapping[0].size = 0x8;
	status = pt_image_add(&ifix->image, &ifix->section[0], &ifix->asid[0],
			      0x1004ull, 1);
	ptu_int_eq(status, 0);

	status = pt_image_add(&ifix->image, &ifix->section[0], &ifix->asid[0],
			      0x100cull, 2);
	ptu_int_eq(status, 0);

	status = pt_image_add(&ifix->image, &ifix->section[1], &ifix->asid[0],
			      0x1000ull, 3);
	ptu_int_eq(status, 0);

	isid = -1;
	status = pt_image_read(&ifix->image, &isid, buffer, 1, &ifix->asid[0],
			       0x1004ull);
	ptu_int_eq(status, 1);
	ptu_int_eq(isid, 3);
	ptu_uint_eq(buffer[0], 0x04);
	ptu_uint_eq(buffer[1], 0xcc);

	isid = -1;
	status = pt_image_read(&ifix->image, &isid, buffer, 1, &ifix->asid[0],
			       0x100cull);
	ptu_int_eq(status, 1);
	ptu_int_eq(isid, 3);
	ptu_uint_eq(buffer[0], 0x0c);
	ptu_uint_eq(buffer[1], 0xcc);

	isid = -1;
	status = pt_image_read(&ifix->image, &isid, buffer, 2, &ifix->asid[0],
			       0x100full);
	ptu_int_eq(status, 1);
	ptu_int_eq(isid, 3);
	ptu_uint_eq(buffer[0], 0x0f);
	ptu_uint_eq(buffer[1], 0xcc);

	isid = -1;
	status = pt_image_read(&ifix->image, &isid, buffer, 1, &ifix->asid[0],
			       0x1010ull);
	ptu_int_eq(status, 1);
	ptu_int_eq(isid, 2);
	ptu_uint_eq(buffer[0], 0x04);
	ptu_uint_eq(buffer[1], 0xcc);

	return ptu_passed();
}