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
typedef  unsigned long long uint64_t ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 int pt_last_ip_query (unsigned long long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_internal ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (unsigned long long,unsigned long long) ; 

__attribute__((used)) static struct ptunit_result query_null(void)
{
	uint64_t ip = 13ull;
	int errcode;

	errcode = pt_last_ip_query(&ip, NULL);
	ptu_int_eq(errcode, -pte_internal);
	ptu_uint_eq(ip, 13ull);

	return ptu_passed();
}