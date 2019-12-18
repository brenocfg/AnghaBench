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
struct pt_asid {int dummy; } ;
struct image_fixture {int /*<<< orphan*/  copy; int /*<<< orphan*/  image; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  pt_asid_init (struct pt_asid*) ; 
 int pt_image_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_image_read (int /*<<< orphan*/ *,int*,int*,int,struct pt_asid*,int) ; 
 int pte_nomap ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int,int) ; 

__attribute__((used)) static struct ptunit_result copy_empty(struct image_fixture *ifix)
{
	struct pt_asid asid;
	uint8_t buffer[] = { 0xcc, 0xcc };
	int status, isid;

	pt_asid_init(&asid);

	status = pt_image_copy(&ifix->copy, &ifix->image);
	ptu_int_eq(status, 0);

	isid = -1;
	status = pt_image_read(&ifix->copy, &isid, buffer, sizeof(buffer),
			       &asid, 0x1000ull);
	ptu_int_eq(status, -pte_nomap);
	ptu_int_eq(isid, -1);
	ptu_uint_eq(buffer[0], 0xcc);
	ptu_uint_eq(buffer[1], 0xcc);

	return ptu_passed();
}