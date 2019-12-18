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
typedef  int /*<<< orphan*/  uint32_t ;
struct time_fixture {int /*<<< orphan*/  time; } ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 int pt_time_query_cbr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_internal ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result query_cbr_null(struct time_fixture *tfix)
{
	uint32_t cbr;
	int errcode;

	errcode = pt_time_query_cbr(NULL, &tfix->time);
	ptu_int_eq(errcode, -pte_internal);

	errcode = pt_time_query_cbr(&cbr, NULL);
	ptu_int_eq(errcode, -pte_internal);

	return ptu_passed();
}