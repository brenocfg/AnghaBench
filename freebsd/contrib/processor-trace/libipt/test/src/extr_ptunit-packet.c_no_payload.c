#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ptunit_result {int dummy; } ;
struct packet_fixture {TYPE_1__* packet; } ;
typedef  enum pt_packet_type { ____Placeholder_pt_packet_type } pt_packet_type ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  pfix_test ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,struct packet_fixture*) ; 

__attribute__((used)) static struct ptunit_result no_payload(struct packet_fixture *pfix,
				       enum pt_packet_type type)
{
	pfix->packet[0].type = type;

	ptu_test(pfix_test, pfix);

	return ptu_passed();
}