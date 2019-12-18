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
struct pt_last_ip {unsigned long long ip; int have_ip; scalar_t__ suppressed; } ;

/* Variables and functions */
 int pt_last_ip_query (unsigned long long*,struct pt_last_ip*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (unsigned long long,unsigned long long) ; 

__attribute__((used)) static struct ptunit_result query(void)
{
	struct pt_last_ip last_ip;
	uint64_t ip, exp = 42ull;
	int errcode;

	last_ip.ip = 42ull;
	last_ip.have_ip = 1;
	last_ip.suppressed = 0;

	errcode = pt_last_ip_query(&ip, &last_ip);
	ptu_int_eq(errcode, 0);
	ptu_uint_eq(last_ip.ip, exp);

	return ptu_passed();
}