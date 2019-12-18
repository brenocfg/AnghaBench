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
struct time_fixture {int /*<<< orphan*/  time; } ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 int pt_time_query_tsc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_no_time ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result query_tsc_none(struct time_fixture *tfix)
{
	uint64_t tsc;
	int errcode;

	errcode = pt_time_query_tsc(&tsc, NULL, NULL, &tfix->time);
	ptu_int_eq(errcode, -pte_no_time);

	return ptu_passed();
}