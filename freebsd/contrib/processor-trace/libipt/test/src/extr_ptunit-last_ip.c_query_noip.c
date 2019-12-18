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
struct pt_last_ip {unsigned long long ip; scalar_t__ suppressed; scalar_t__ have_ip; } ;

/* Variables and functions */
 int pt_last_ip_query (unsigned long long*,struct pt_last_ip*) ; 
 int /*<<< orphan*/  pte_noip ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (unsigned long long,unsigned long long) ; 

__attribute__((used)) static struct ptunit_result query_noip(void)
{
	struct pt_last_ip last_ip;
	uint64_t ip = 13ull;
	int errcode;

	last_ip.ip = 42ull;
	last_ip.have_ip = 0;
	last_ip.suppressed = 0;

	errcode = pt_last_ip_query(&ip, &last_ip);
	ptu_int_eq(errcode, -pte_noip);
	ptu_uint_eq(ip, 0ull);

	return ptu_passed();
}