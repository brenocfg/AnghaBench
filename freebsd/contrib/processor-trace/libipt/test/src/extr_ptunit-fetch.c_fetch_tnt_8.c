#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ptunit_result {int dummy; } ;
struct TYPE_3__ {int bit_size; } ;
struct TYPE_4__ {TYPE_1__ tnt; } ;
struct pt_packet {TYPE_2__ payload; int /*<<< orphan*/  type; } ;
struct fetch_fixture {int dummy; } ;
typedef  int /*<<< orphan*/  packet ;

/* Variables and functions */
 int /*<<< orphan*/  fetch_packet ; 
 int /*<<< orphan*/  memset (struct pt_packet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppt_tnt_8 ; 
 int /*<<< orphan*/  pt_decode_tnt_8 ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,struct fetch_fixture*,struct pt_packet*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ptunit_result fetch_tnt_8(struct fetch_fixture *ffix)
{
	struct pt_packet packet;

	memset(&packet, 0, sizeof(packet));
	packet.type = ppt_tnt_8;
	packet.payload.tnt.bit_size = 1;

	ptu_test(fetch_packet, ffix, &packet, &pt_decode_tnt_8);

	return ptu_passed();
}