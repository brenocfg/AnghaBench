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
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IPFW_ADD_OBJ_REWRITER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPFW_ADD_SOPT_HANDLER (int,int /*<<< orphan*/ ) ; 
 scalar_t__ V_nat64stl_eid ; 
 scalar_t__ ipfw_add_eaction (struct ip_fw_chain*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ipfw_nat64stl ; 
 int /*<<< orphan*/  opcodes ; 
 int /*<<< orphan*/  scodes ; 

int
nat64stl_init(struct ip_fw_chain *ch, int first)
{

	V_nat64stl_eid = ipfw_add_eaction(ch, ipfw_nat64stl, "nat64stl");
	if (V_nat64stl_eid == 0)
		return (ENXIO);
	IPFW_ADD_SOPT_HANDLER(first, scodes);
	IPFW_ADD_OBJ_REWRITER(first, opcodes);
	return (0);
}