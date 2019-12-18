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
struct time_fixture {int /*<<< orphan*/  config; int /*<<< orphan*/  time; } ;
struct ptunit_result {int dummy; } ;
struct pt_packet_tma {int ctc; int fc; } ;

/* Variables and functions */
 int pt_time_update_tma (int /*<<< orphan*/ *,struct pt_packet_tma*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_bad_context ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result tma(struct time_fixture *tfix)
{
	struct pt_packet_tma packet;
	int errcode;

	packet.ctc = 0xdc;
	packet.fc = 0xf;

	errcode = pt_time_update_tma(&tfix->time, &packet, &tfix->config);
	ptu_int_eq(errcode, -pte_bad_context);

	return ptu_passed();
}