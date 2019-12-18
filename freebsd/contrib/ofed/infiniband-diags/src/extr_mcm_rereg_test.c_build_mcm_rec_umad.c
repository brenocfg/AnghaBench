#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  rpc ;
struct TYPE_5__ {scalar_t__ mod; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int method; int /*<<< orphan*/  dataoffs; int /*<<< orphan*/  datasz; int /*<<< orphan*/  mask; TYPE_1__ attr; int /*<<< orphan*/  mgtclass; } ;
typedef  TYPE_2__ ib_rpc_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SA_ATTR_MCRECORD ; 
 int /*<<< orphan*/  IB_SA_CLASS ; 
 int /*<<< orphan*/  IB_SA_DATA_OFFS ; 
 int /*<<< orphan*/  IB_SA_DATA_SIZE ; 
 int /*<<< orphan*/  mad_build_pkt (void*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void build_mcm_rec_umad(void *umad, ib_portid_t * dport, int method,
			       uint64_t comp_mask, uint8_t * data)
{
	ib_rpc_t rpc;

	memset(&rpc, 0, sizeof(rpc));
	rpc.mgtclass = IB_SA_CLASS;
	rpc.method = method;
	rpc.attr.id = IB_SA_ATTR_MCRECORD;
	rpc.attr.mod = 0;	// ???
	rpc.mask = comp_mask;
	rpc.datasz = IB_SA_DATA_SIZE;
	rpc.dataoffs = IB_SA_DATA_OFFS;

	mad_build_pkt(umad, &rpc, dport, NULL, data);
}