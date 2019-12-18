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
typedef  int /*<<< orphan*/  uint64_t ;
struct ptunit_result {int dummy; } ;
struct pt_last_ip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_last_ip_init (struct pt_last_ip*) ; 
 int pt_last_ip_query (int /*<<< orphan*/ *,struct pt_last_ip*) ; 
 int /*<<< orphan*/  pte_noip ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result query_initial(void)
{
	struct pt_last_ip last_ip;
	uint64_t ip;
	int errcode;

	pt_last_ip_init(&last_ip);

	errcode = pt_last_ip_query(&ip, &last_ip);
	ptu_int_eq(errcode, -pte_noip);

	return ptu_passed();
}