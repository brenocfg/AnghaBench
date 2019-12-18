#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_14__ {scalar_t__ lid; } ;
typedef  TYPE_5__ ib_portid_t ;
struct TYPE_12__ {int dr_slid; int method; int /*<<< orphan*/  mkey; int /*<<< orphan*/  attr_mod; int /*<<< orphan*/  attr_id; void* lid; } ;
struct TYPE_13__ {TYPE_3__ ntc_256; } ;
struct TYPE_10__ {void* trap_num; void* prod_type_lsb; } ;
struct TYPE_11__ {TYPE_1__ generic; } ;
struct TYPE_15__ {int generic_type; TYPE_4__ data_details; void* issuer_lid; TYPE_2__ g_or_v; } ;
typedef  TYPE_6__ ib_mad_notice_attr_t ;

/* Variables and functions */
 int IB_NOTICE_TYPE_SECURITY ; 
 void* cl_hton16 (int) ; 
 int /*<<< orphan*/  cl_ntoh16 (int) ; 
 int /*<<< orphan*/  cl_ntoh32 (int) ; 
 int /*<<< orphan*/  cl_ntoh64 (int) ; 
 int get_node_type (TYPE_5__*) ; 

__attribute__((used)) static void build_trap256_local(ib_mad_notice_attr_t * n, ib_portid_t * port)
{
	n->generic_type = 0x80 | IB_NOTICE_TYPE_SECURITY;
	n->g_or_v.generic.prod_type_lsb = cl_hton16(get_node_type(port));
	n->g_or_v.generic.trap_num = cl_hton16(256);
	n->issuer_lid = cl_hton16((uint16_t) port->lid);
	n->data_details.ntc_256.lid = n->issuer_lid;
	n->data_details.ntc_256.dr_slid = 0xffff;
	n->data_details.ntc_256.method = 1;
	n->data_details.ntc_256.attr_id = cl_ntoh16(0x15);
	n->data_details.ntc_256.attr_mod = cl_ntoh32(0x12);
	n->data_details.ntc_256.mkey = cl_ntoh64(0x1234567812345678);
}