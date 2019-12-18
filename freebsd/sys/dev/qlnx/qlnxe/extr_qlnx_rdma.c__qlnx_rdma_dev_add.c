#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qlnx_host {scalar_t__ personality; TYPE_1__* qlnx_rdma; } ;
struct TYPE_4__ {TYPE_1__* (* add ) (struct qlnx_host*) ;} ;

/* Variables and functions */
 scalar_t__ ECORE_PCI_ETH_IWARP ; 
 scalar_t__ ECORE_PCI_ETH_ROCE ; 
 int /*<<< orphan*/  QL_DPRINT12 (struct qlnx_host*,char*,struct qlnx_host*,TYPE_1__*) ; 
 TYPE_1__* qlnx_rdma_if ; 
 TYPE_1__* stub1 (struct qlnx_host*) ; 

__attribute__((used)) static void
_qlnx_rdma_dev_add(struct qlnx_host *ha)
{
	QL_DPRINT12(ha, "enter ha = %p qlnx_rdma_if = %p\n", ha, qlnx_rdma_if);

	if (qlnx_rdma_if == NULL) 
		return;

	if (ha->personality != ECORE_PCI_ETH_IWARP && 
		ha->personality != ECORE_PCI_ETH_ROCE)
		return;

	ha->qlnx_rdma = qlnx_rdma_if->add(ha);

	QL_DPRINT12(ha, "exit (ha = %p, qlnx_rdma = %p)\n", ha, ha->qlnx_rdma);
	return;
}