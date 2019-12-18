#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct ptunit_result {int dummy; } ;
struct image_fixture {int /*<<< orphan*/ * asid; int /*<<< orphan*/  image; TYPE_1__* mapping; } ;
struct TYPE_2__ {int errcode; } ;

/* Variables and functions */
 int pt_image_read (int /*<<< orphan*/ *,int*,int*,int,int /*<<< orphan*/ *,int) ; 
 int pte_nosync ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int,int) ; 

__attribute__((used)) static struct ptunit_result read_error(struct image_fixture *ifix)
{
	uint8_t buffer[] = { 0xcc };
	int status, isid;

	ifix->mapping[0].errcode = -pte_nosync;

	isid = -1;
	status = pt_image_read(&ifix->image, &isid, buffer, 1, &ifix->asid[0],
			       0x1000ull);
	ptu_int_eq(status, -pte_nosync);
	ptu_int_eq(isid, 10);
	ptu_uint_eq(buffer[0], 0xcc);

	return ptu_passed();
}