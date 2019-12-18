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
struct time_fixture {int /*<<< orphan*/  time; int /*<<< orphan*/  config; } ;
struct ptunit_result {int dummy; } ;
struct pt_packet_mtc {int ctc; } ;

/* Variables and functions */
 int pt_time_query_tsc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_time_update_mtc (int /*<<< orphan*/ *,struct pt_packet_mtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_no_time ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result mtc(struct time_fixture *tfix)
{
	struct pt_packet_mtc packet;
	uint64_t tsc;
	int errcode;

	packet.ctc = 0xdc;

	errcode = pt_time_update_mtc(&tfix->time, &packet, &tfix->config);
	ptu_int_eq(errcode, 0);

	errcode = pt_time_query_tsc(&tsc, NULL, NULL, &tfix->time);
	ptu_int_eq(errcode, -pte_no_time);

	return ptu_passed();
}