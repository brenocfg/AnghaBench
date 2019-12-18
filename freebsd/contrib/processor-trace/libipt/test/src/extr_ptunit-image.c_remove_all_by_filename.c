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
struct image_fixture {int /*<<< orphan*/ * asid; int /*<<< orphan*/  image; TYPE_1__* status; TYPE_2__* section; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_4__ {char* filename; } ;
struct TYPE_3__ {int /*<<< orphan*/  deleted; } ;

/* Variables and functions */
 int pt_image_add (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int,int) ; 
 int pt_image_read (int /*<<< orphan*/ *,int*,int*,int,int /*<<< orphan*/ *,int) ; 
 int pt_image_remove_by_filename (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int pte_nomap ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 int /*<<< orphan*/  ptu_int_ne (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int,int) ; 

__attribute__((used)) static struct ptunit_result remove_all_by_filename(struct image_fixture *ifix)
{
	uint8_t buffer[] = { 0xcc, 0xcc, 0xcc };
	int status, isid;

	ifix->section[0].filename = "same-name";
	ifix->section[1].filename = "same-name";

	status = pt_image_add(&ifix->image, &ifix->section[0], &ifix->asid[0],
			      0x1000ull, 1);
	ptu_int_eq(status, 0);

	status = pt_image_add(&ifix->image, &ifix->section[1], &ifix->asid[0],
			      0x2000ull, 2);
	ptu_int_eq(status, 0);

	isid = -1;
	status = pt_image_read(&ifix->image, &isid, buffer, 2, &ifix->asid[0],
			       0x1001ull);
	ptu_int_eq(status, 2);
	ptu_int_eq(isid, 1);
	ptu_uint_eq(buffer[0], 0x01);
	ptu_uint_eq(buffer[1], 0x02);
	ptu_uint_eq(buffer[2], 0xcc);

	status = pt_image_remove_by_filename(&ifix->image, "same-name",
					     &ifix->asid[0]);
	ptu_int_eq(status, 2);

	ptu_int_ne(ifix->status[0].deleted, 0);
	ptu_int_ne(ifix->status[1].deleted, 0);

	isid = -1;
	status = pt_image_read(&ifix->image, &isid, buffer, sizeof(buffer),
			       &ifix->asid[0], 0x1003ull);
	ptu_int_eq(status, -pte_nomap);
	ptu_int_eq(isid, -1);
	ptu_uint_eq(buffer[0], 0x01);
	ptu_uint_eq(buffer[1], 0x02);
	ptu_uint_eq(buffer[2], 0xcc);

	isid = -1;
	status = pt_image_read(&ifix->image, &isid, buffer, sizeof(buffer),
			       &ifix->asid[0], 0x2003ull);
	ptu_int_eq(status, -pte_nomap);
	ptu_int_eq(isid, -1);
	ptu_uint_eq(buffer[0], 0x01);
	ptu_uint_eq(buffer[1], 0x02);
	ptu_uint_eq(buffer[2], 0xcc);

	return ptu_passed();
}