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
typedef  int uint64_t ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 int pt_retstack_pop (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pte_invalid ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int,int) ; 

__attribute__((used)) static struct ptunit_result query_null(void)
{
	uint64_t ip;
	int status;

	ip = 0x42ull;
	status = pt_retstack_pop(NULL, &ip);
	ptu_int_eq(status, -pte_invalid);
	ptu_uint_eq(ip, 0x42ull);

	return ptu_passed();
}