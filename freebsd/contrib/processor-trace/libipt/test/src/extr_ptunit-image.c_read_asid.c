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
struct ptunit_result {int dummy; } ;
struct image_fixture {int /*<<< orphan*/ * asid; int /*<<< orphan*/  image; int /*<<< orphan*/ * section; } ;

/* Variables and functions */
 int pt_image_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int pt_image_read (int /*<<< orphan*/ *,int*,int*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int,int) ; 

__attribute__((used)) static struct ptunit_result read_asid(struct image_fixture *ifix)
{
	uint8_t buffer[] = { 0xcc, 0xcc };
	int status, isid;

	status = pt_image_add(&ifix->image, &ifix->section[0], &ifix->asid[0],
			      0x1000ull, 1);
	ptu_int_eq(status, 0);

	status = pt_image_add(&ifix->image, &ifix->section[1], &ifix->asid[1],
			      0x1008ull, 2);
	ptu_int_eq(status, 0);

	isid = -1;
	status = pt_image_read(&ifix->image, &isid, buffer, 1, &ifix->asid[0],
			       0x1009ull);
	ptu_int_eq(status, 1);
	ptu_int_eq(isid, 1);
	ptu_uint_eq(buffer[0], 0x09);
	ptu_uint_eq(buffer[1], 0xcc);

	isid = -1;
	status = pt_image_read(&ifix->image, &isid, buffer, 1, &ifix->asid[1],
			       0x1009ull);
	ptu_int_eq(status, 1);
	ptu_int_eq(isid, 2);
	ptu_uint_eq(buffer[0], 0x01);
	ptu_uint_eq(buffer[1], 0xcc);

	return ptu_passed();
}