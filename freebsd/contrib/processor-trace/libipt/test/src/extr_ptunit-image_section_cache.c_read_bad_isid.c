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
struct iscache_fixture {int /*<<< orphan*/  iscache; int /*<<< orphan*/ * section; } ;

/* Variables and functions */
 int pt_iscache_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int pt_iscache_read (int /*<<< orphan*/ *,int*,unsigned long long,int,int) ; 
 int /*<<< orphan*/  pte_bad_image ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_int_gt (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int,int) ; 

__attribute__((used)) static struct ptunit_result read_bad_isid(struct iscache_fixture *cfix)
{
	uint8_t buffer[] = { 0xcc };
	int status, isid;

	isid = pt_iscache_add(&cfix->iscache, cfix->section[0], 0xa000ull);
	ptu_int_gt(isid, 0);

	status = pt_iscache_read(&cfix->iscache, buffer, 1ull, isid + 1,
				 0xa000ull);
	ptu_int_eq(status, -pte_bad_image);
	ptu_uint_eq(buffer[0], 0xcc);

	return ptu_passed();
}