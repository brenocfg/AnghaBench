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
typedef  size_t uint32_t ;
struct snmp_pdu {size_t nbindings; scalar_t__ version; TYPE_1__* bindings; } ;
typedef  int int32_t ;
struct TYPE_2__ {scalar_t__ syntax; int /*<<< orphan*/  var; } ;

/* Variables and functions */
 scalar_t__ SNMP_SYNTAX_ENDOFMIBVIEW ; 
 scalar_t__ SNMP_V1 ; 
 scalar_t__ asn_is_suboid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int32_t
snmp_parse_getnext_resp(struct snmp_pdu *resp, struct snmp_pdu *req)
{
	uint32_t i;

	for (i = 0; i < req->nbindings; i++) {
		if (asn_is_suboid(&req->bindings[i].var, &resp->bindings[i].var)
		    == 0)
			return (0);

		if (resp->version != SNMP_V1 && resp->bindings[i].syntax ==
		    SNMP_SYNTAX_ENDOFMIBVIEW)
			return (0);
	}

	return (1);
}