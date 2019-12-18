#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct query_params {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  capability_mask; int /*<<< orphan*/  master_sm_base_lid; int /*<<< orphan*/  base_lid; } ;
struct TYPE_3__ {int port_num; int /*<<< orphan*/  lid; TYPE_2__ port_info; } ;
typedef  TYPE_1__ ib_portinfo_record_t ;
typedef  TYPE_2__ ib_port_info_t ;

/* Variables and functions */
 int cl_ntoh16 (int /*<<< orphan*/ ) ; 
 int cl_ntoh32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int) ; 

__attribute__((used)) static void dump_portinfo_record(void *data, struct query_params *p)
{
	ib_portinfo_record_t *p_pir = data;
	const ib_port_info_t *const p_pi = &p_pir->port_info;

	printf("PortInfoRecord dump:\n"
	       "\t\tEndPortLid..............%u\n"
	       "\t\tPortNum.................%u\n"
	       "\t\tbase_lid................%u\n"
	       "\t\tmaster_sm_base_lid......%u\n"
	       "\t\tcapability_mask.........0x%X\n",
	       cl_ntoh16(p_pir->lid), p_pir->port_num,
	       cl_ntoh16(p_pi->base_lid), cl_ntoh16(p_pi->master_sm_base_lid),
	       cl_ntoh32(p_pi->capability_mask));
}