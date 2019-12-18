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
struct time_fixture {int /*<<< orphan*/  tcal; int /*<<< orphan*/  config; } ;
struct ptunit_result {int dummy; } ;
struct pt_packet_mtc {int dummy; } ;

/* Variables and functions */
 int pt_tcal_update_mtc (int /*<<< orphan*/ *,struct pt_packet_mtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_internal ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result tcal_mtc_null(struct time_fixture *tfix)
{
	struct pt_packet_mtc packet;
	int errcode;

	errcode = pt_tcal_update_mtc(NULL, &packet, &tfix->config);
	ptu_int_eq(errcode, -pte_internal);

	errcode = pt_tcal_update_mtc(&tfix->tcal, NULL, &tfix->config);
	ptu_int_eq(errcode, -pte_internal);

	errcode = pt_tcal_update_mtc(&tfix->tcal, &packet, NULL);
	ptu_int_eq(errcode, -pte_internal);

	return ptu_passed();
}