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
struct time_fixture {int /*<<< orphan*/  time; int /*<<< orphan*/  config; } ;
struct ptunit_result {int dummy; } ;
struct pt_packet_tma {int dummy; } ;

/* Variables and functions */
 int pt_time_update_tma (int /*<<< orphan*/ *,struct pt_packet_tma*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_internal ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result tma_null(struct time_fixture *tfix)
{
	struct pt_packet_tma packet;
	int errcode;

	errcode = pt_time_update_tma(NULL, &packet, &tfix->config);
	ptu_int_eq(errcode, -pte_internal);

	errcode = pt_time_update_tma(&tfix->time, NULL, &tfix->config);
	ptu_int_eq(errcode, -pte_internal);

	errcode = pt_time_update_tma(&tfix->time, &packet, NULL);
	ptu_int_eq(errcode, -pte_internal);

	return ptu_passed();
}