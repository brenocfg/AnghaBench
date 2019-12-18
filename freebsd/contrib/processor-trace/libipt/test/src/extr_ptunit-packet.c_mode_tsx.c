#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ptunit_result {int dummy; } ;
struct packet_fixture {TYPE_5__* packet; } ;
struct TYPE_6__ {int intx; } ;
struct TYPE_7__ {TYPE_1__ tsx; } ;
struct TYPE_8__ {TYPE_2__ bits; int /*<<< orphan*/  leaf; } ;
struct TYPE_9__ {TYPE_3__ mode; } ;
struct TYPE_10__ {TYPE_4__ payload; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  pfix_test ; 
 int /*<<< orphan*/  ppt_mode ; 
 int /*<<< orphan*/  pt_mol_tsx ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,struct packet_fixture*) ; 

__attribute__((used)) static struct ptunit_result mode_tsx(struct packet_fixture *pfix)
{
	pfix->packet[0].type = ppt_mode;
	pfix->packet[0].payload.mode.leaf = pt_mol_tsx;
	pfix->packet[0].payload.mode.bits.tsx.intx = 1;

	ptu_test(pfix_test, pfix);

	return ptu_passed();
}