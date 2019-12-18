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
struct time_fixture {int /*<<< orphan*/  time; int /*<<< orphan*/  config; int /*<<< orphan*/  tcal; } ;
struct ptunit_result {int dummy; } ;
struct pt_packet_cyc {int value; } ;

/* Variables and functions */
 int pt_tcal_fcr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_time_query_tsc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_time_update_cyc (int /*<<< orphan*/ *,struct pt_packet_cyc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_no_time ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result cyc(struct time_fixture *tfix)
{
	struct pt_packet_cyc packet;
	uint64_t fcr, tsc;
	int errcode;

	errcode = pt_tcal_fcr(&fcr, &tfix->tcal);
	ptu_int_eq(errcode, 0);

	packet.value = 0xdc;

	errcode = pt_time_update_cyc(&tfix->time, &packet, &tfix->config, fcr);
	ptu_int_eq(errcode, 0);

	errcode = pt_time_query_tsc(&tsc, NULL, NULL, &tfix->time);
	ptu_int_eq(errcode, -pte_no_time);

	return ptu_passed();
}