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
typedef  int /*<<< orphan*/  uint32_t ;
struct time_fixture {int /*<<< orphan*/  time; int /*<<< orphan*/  config; } ;
struct ptunit_result {int dummy; } ;
struct pt_packet_tsc {int tsc; } ;

/* Variables and functions */
 int pt_time_query_tsc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_time_update_tsc (int /*<<< orphan*/ *,struct pt_packet_tsc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ptunit_result tsc(struct time_fixture *tfix)
{
	struct pt_packet_tsc packet;
	uint64_t tsc;
	uint32_t lost_mtc, lost_cyc;
	int errcode;

	packet.tsc = 0xdedededeull;

	errcode = pt_time_update_tsc(&tfix->time, &packet, &tfix->config);
	ptu_int_eq(errcode, 0);

	errcode = pt_time_query_tsc(&tsc, &lost_mtc, &lost_cyc, &tfix->time);
	ptu_int_eq(errcode, 0);

	ptu_uint_eq(tsc, 0xdedededeull);
	ptu_uint_eq(lost_mtc, 0);
	ptu_uint_eq(lost_cyc, 0);

	return ptu_passed();
}