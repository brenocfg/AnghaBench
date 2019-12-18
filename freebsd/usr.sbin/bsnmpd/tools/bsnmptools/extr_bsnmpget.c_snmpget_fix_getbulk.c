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
typedef  scalar_t__ uint32_t ;
struct snmp_pdu {scalar_t__ nbindings; scalar_t__ error_status; int error_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
snmpget_fix_getbulk(struct snmp_pdu *pdu, uint32_t max_rep, uint32_t non_rep)
{
	assert(pdu != NULL);

	if (pdu->nbindings < non_rep)
		pdu->error_status = pdu->nbindings;
	else
		pdu->error_status = non_rep;

	if (max_rep > 0)
		pdu->error_index = max_rep;
	else
		pdu->error_index = 1;
}