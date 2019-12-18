#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  rc_cap_mask ;
struct TYPE_6__ {size_t lid; int /*<<< orphan*/  sl; } ;
typedef  TYPE_1__ ib_portid_t ;
struct TYPE_7__ {int /*<<< orphan*/  pma_query_failures; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_PORT_INFO ; 
 int /*<<< orphan*/  IBWARN (char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ibd_timeout ; 
 int /*<<< orphan*/  ibmad_port ; 
 int /*<<< orphan*/ * lid2sl_table ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pma_query_via (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portid2str (TYPE_1__*) ; 
 TYPE_2__ summary ; 

__attribute__((used)) static int query_cap_mask(ib_portid_t * portid, char *node_name, int portnum,
			  uint16_t * cap_mask)
{
	uint8_t pc[1024] = { 0 };
	uint16_t rc_cap_mask;

	portid->sl = lid2sl_table[portid->lid];

	/* PerfMgt ClassPortInfo is a required attribute */
	if (!pma_query_via(pc, portid, portnum, ibd_timeout, CLASS_PORT_INFO,
			   ibmad_port)) {
		IBWARN("classportinfo query failed on %s, %s port %d",
		       node_name, portid2str(portid), portnum);
		summary.pma_query_failures++;
		return -1;
	}

	/* ClassPortInfo should be supported as part of libibmad */
	memcpy(&rc_cap_mask, pc + 2, sizeof(rc_cap_mask));	/* CapabilityMask */

	*cap_mask = rc_cap_mask;
	return 0;
}