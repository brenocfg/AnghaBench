#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_23__ {scalar_t__ lid; } ;
typedef  TYPE_9__ ib_portid_t ;
struct TYPE_19__ {void* interface_id; void* prefix; } ;
struct TYPE_20__ {TYPE_5__ unicast; } ;
struct TYPE_17__ {void* interface_id; void* prefix; } ;
struct TYPE_18__ {TYPE_3__ unicast; } ;
struct TYPE_21__ {TYPE_6__ gid2; TYPE_4__ gid1; void* qp2; void* qp1; void* key; void* lid2; void* lid1; } ;
struct TYPE_22__ {TYPE_7__ ntc_257_258; } ;
struct TYPE_15__ {void* trap_num; void* prod_type_lsb; } ;
struct TYPE_16__ {TYPE_1__ generic; } ;
struct TYPE_14__ {int generic_type; TYPE_8__ data_details; void* issuer_lid; TYPE_2__ g_or_v; } ;
typedef  TYPE_10__ ib_mad_notice_attr_t ;

/* Variables and functions */
 int IB_NOTICE_TYPE_SECURITY ; 
 void* cl_hton16 (int) ; 
 void* cl_hton32 (int) ; 
 void* cl_ntoh64 (int) ; 
 int get_node_type (TYPE_9__*) ; 

__attribute__((used)) static void build_trap257_258(ib_mad_notice_attr_t * n, ib_portid_t * port,
			      uint16_t trap_num)
{
	n->generic_type = 0x80 | IB_NOTICE_TYPE_SECURITY;
	n->g_or_v.generic.prod_type_lsb = cl_hton16(get_node_type(port));
	n->g_or_v.generic.trap_num = cl_hton16(trap_num);
	n->issuer_lid = cl_hton16((uint16_t) port->lid);
	n->data_details.ntc_257_258.lid1 = cl_hton16(1);
	n->data_details.ntc_257_258.lid2 = cl_hton16(2);
	n->data_details.ntc_257_258.key = cl_hton32(0x12345678);
	n->data_details.ntc_257_258.qp1 = cl_hton32(0x010101);
	n->data_details.ntc_257_258.qp2 = cl_hton32(0x020202);
	n->data_details.ntc_257_258.gid1.unicast.prefix = cl_ntoh64(0xf8c0000000000001);
	n->data_details.ntc_257_258.gid1.unicast.interface_id = cl_ntoh64(0x1111222233334444);
	n->data_details.ntc_257_258.gid2.unicast.prefix = cl_ntoh64(0xf8c0000000000001);
	n->data_details.ntc_257_258.gid2.unicast.interface_id = cl_ntoh64(0x5678567812341234);
}