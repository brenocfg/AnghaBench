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
struct time_fixture {int /*<<< orphan*/  time; int /*<<< orphan*/  config; } ;
struct ptunit_result {int dummy; } ;
struct pt_packet_cbr {int ratio; } ;

/* Variables and functions */
 int pt_time_query_cbr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_time_update_cbr (int /*<<< orphan*/ *,struct pt_packet_cbr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ptunit_result cbr(struct time_fixture *tfix)
{
	struct pt_packet_cbr packet;
	uint32_t cbr;
	int errcode;

	packet.ratio = 0x38;

	errcode = pt_time_update_cbr(&tfix->time, &packet, &tfix->config);
	ptu_int_eq(errcode, 0);

	errcode = pt_time_query_cbr(&cbr, &tfix->time);
	ptu_int_eq(errcode, 0);

	ptu_uint_eq(cbr, 0x38);

	return ptu_passed();
}