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
struct pt_retstack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_retstack_init (struct pt_retstack*) ; 
 int pt_retstack_pop (struct pt_retstack*,int*) ; 
 int /*<<< orphan*/  pte_retstack_empty ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int,int) ; 

__attribute__((used)) static struct ptunit_result query_empty(void)
{
	struct pt_retstack retstack;
	uint64_t ip;
	int status;

	pt_retstack_init(&retstack);

	ip = 0x42ull;
	status = pt_retstack_pop(&retstack, &ip);
	ptu_int_eq(status, -pte_retstack_empty);
	ptu_uint_eq(ip, 0x42ull);

	return ptu_passed();
}