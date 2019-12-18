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
struct image_fixture {int /*<<< orphan*/ * asid; int /*<<< orphan*/  image; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int pt_image_read (int /*<<< orphan*/ *,int*,int*,int,int /*<<< orphan*/ *,int) ; 
 int pte_nomap ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int,int) ; 

__attribute__((used)) static struct ptunit_result read_bad_asid(struct image_fixture *ifix)
{
	uint8_t buffer[] = { 0xcc, 0xcc };
	int status, isid;

	isid = -1;
	status = pt_image_read(&ifix->image, &isid, buffer, sizeof(buffer),
			       &ifix->asid[0], 0x2003ull);
	ptu_int_eq(status, -pte_nomap);
	ptu_int_eq(isid, -1);
	ptu_uint_eq(buffer[0], 0xcc);
	ptu_uint_eq(buffer[1], 0xcc);

	return ptu_passed();
}