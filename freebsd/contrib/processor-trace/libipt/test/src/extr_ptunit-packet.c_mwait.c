#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ptunit_result {int dummy; } ;
struct packet_fixture {TYPE_3__* packet; } ;
struct TYPE_4__ {int hints; int ext; } ;
struct TYPE_5__ {TYPE_1__ mwait; } ;
struct TYPE_6__ {TYPE_2__ payload; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  pfix_test ; 
 int /*<<< orphan*/  ppt_mwait ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,struct packet_fixture*) ; 

__attribute__((used)) static struct ptunit_result mwait(struct packet_fixture *pfix)
{
	pfix->packet[0].type = ppt_mwait;
	pfix->packet[0].payload.mwait.hints = 0xc;
	pfix->packet[0].payload.mwait.ext = 0x1;

	ptu_test(pfix_test, pfix);

	return ptu_passed();
}