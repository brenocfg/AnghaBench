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
struct pt_asid {int cr3; int vmcs; int size; } ;
typedef  int /*<<< orphan*/  asid ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_asid*,int,int) ; 
 int /*<<< orphan*/  pt_asid_init (struct pt_asid*) ; 
 int pt_asid_to_user (struct pt_asid*,struct pt_asid*,int) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int,int) ; 

__attribute__((used)) static struct ptunit_result to_user_big(void)
{
	struct pt_asid asid, user;
	int errcode;

	memset(&user, 0xcc, sizeof(user));
	pt_asid_init(&asid);
	asid.cr3 = 0x4200ull;
	asid.vmcs = 0x23000ull;

	errcode = pt_asid_to_user(&user, &asid, sizeof(user) + 8);
	ptu_int_eq(errcode, 0);
	ptu_uint_eq(user.size, sizeof(asid));
	ptu_uint_eq(user.cr3, 0x4200ull);
	ptu_uint_eq(user.vmcs, 0x23000ull);

	return ptu_passed();
}