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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/ * bridge_id ;

/* Variables and functions */
 int SNMP_BRIDGE_ID_LEN ; 

__attribute__((used)) static void
snmp_uint64_to_bridgeid(uint64_t id, bridge_id b_id)
{
	int i;
	u_char *o;

	o = (u_char *) &id;

	for (i = 0; i < SNMP_BRIDGE_ID_LEN; i++, o++)
		b_id[SNMP_BRIDGE_ID_LEN - i - 1] = *o;
}