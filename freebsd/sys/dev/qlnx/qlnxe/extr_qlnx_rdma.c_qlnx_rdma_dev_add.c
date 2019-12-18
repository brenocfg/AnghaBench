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
struct qlnx_host {scalar_t__ personality; struct qlnx_host* next; } ;

/* Variables and functions */
 scalar_t__ ECORE_PCI_ETH_IWARP ; 
 scalar_t__ ECORE_PCI_ETH_ROCE ; 
 int /*<<< orphan*/  QL_DPRINT12 (struct qlnx_host*,char*,struct qlnx_host*) ; 
 int /*<<< orphan*/  _qlnx_rdma_dev_add (struct qlnx_host*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct qlnx_host* qlnx_host_list ; 
 int /*<<< orphan*/  qlnx_rdma_dev_lock ; 

void
qlnx_rdma_dev_add(struct qlnx_host *ha)
{
	QL_DPRINT12(ha, "enter ha = %p\n", ha);

	if (ha->personality != ECORE_PCI_ETH_IWARP &&
			ha->personality != ECORE_PCI_ETH_ROCE)
		return;

	mtx_lock(&qlnx_rdma_dev_lock);

	if (qlnx_host_list == NULL) {
		qlnx_host_list = ha;
		ha->next = NULL;
	} else {
		ha->next = qlnx_host_list;
		qlnx_host_list = ha;
	}

	mtx_unlock(&qlnx_rdma_dev_lock);

	_qlnx_rdma_dev_add(ha);
	
	QL_DPRINT12(ha, "exit (%p)\n", ha);

	return;
}