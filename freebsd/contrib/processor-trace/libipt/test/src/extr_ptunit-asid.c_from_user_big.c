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
typedef  int /*<<< orphan*/  user ;
struct ptunit_result {int dummy; } ;
struct pt_asid {int size; int cr3; int vmcs; } ;
typedef  int /*<<< orphan*/  asid ;

/* Variables and functions */
 int pt_asid_from_user (struct pt_asid*,struct pt_asid*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int,int) ; 

__attribute__((used)) static struct ptunit_result from_user_big(void)
{
	struct pt_asid asid, user;
	int errcode;

	user.size = sizeof(user) + 4;
	user.cr3 = 0x4200ull;
	user.vmcs = 0x23000ull;

	errcode = pt_asid_from_user(&asid, &user);
	ptu_int_eq(errcode, 0);
	ptu_uint_eq(asid.size, sizeof(asid));
	ptu_uint_eq(asid.cr3, 0x4200ull);
	ptu_uint_eq(asid.vmcs, 0x23000ull);

	return ptu_passed();
}