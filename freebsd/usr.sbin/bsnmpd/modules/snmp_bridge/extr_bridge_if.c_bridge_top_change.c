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
struct snmp_value {int dummy; } ;
struct bridge_if {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * bridge_basename_var (struct bridge_if*,struct snmp_value*) ; 
 struct bridge_if* bridge_get_default () ; 
 int /*<<< orphan*/  oid_TopologyChange ; 
 int /*<<< orphan*/  oid_begemotNewRoot ; 
 int /*<<< orphan*/  snmp_send_trap (int /*<<< orphan*/ *,struct snmp_value*,...) ; 

__attribute__((used)) static void
bridge_top_change(struct bridge_if *bif)
{
	struct snmp_value bif_idx;

	if (bridge_get_default() == bif)
		snmp_send_trap(&oid_TopologyChange,
		    (struct snmp_value *) NULL);

	if (bridge_basename_var(bif, &bif_idx) == NULL)
		return;

	snmp_send_trap(&oid_begemotNewRoot,
	    &bif_idx, (struct snmp_value *) NULL);
}