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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lisp_eid_action ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void action_flag(netdissect_options *ndo, uint8_t act_auth_inc_res)
{
	uint8_t action;
	uint8_t authoritative;

	authoritative  = ((act_auth_inc_res >> 4) & 1);

	if (authoritative)
		ND_PRINT((ndo, " Authoritative,"));
	else
		ND_PRINT((ndo, " Non-Authoritative,"));

	action = act_auth_inc_res >> 5;
	ND_PRINT((ndo, " %s,", tok2str(lisp_eid_action, "unknown", action)));
}