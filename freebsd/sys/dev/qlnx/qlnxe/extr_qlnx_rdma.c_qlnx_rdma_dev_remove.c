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
typedef  struct qlnx_host qlnx_host_t ;

/* Variables and functions */
 scalar_t__ ECORE_PCI_ETH_IWARP ; 
 scalar_t__ ECORE_PCI_ETH_ROCE ; 
 int /*<<< orphan*/  QL_DPRINT12 (struct qlnx_host*,char*,struct qlnx_host*) ; 
 int _qlnx_rdma_dev_remove (struct qlnx_host*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct qlnx_host* qlnx_host_list ; 
 int /*<<< orphan*/  qlnx_rdma_dev_lock ; 

int
qlnx_rdma_dev_remove(struct qlnx_host *ha)
{
	int ret = 0;
	qlnx_host_t *ha_prev;
	qlnx_host_t *ha_cur;

	QL_DPRINT12(ha, "enter ha = %p\n", ha);

	if ((qlnx_host_list == NULL) || (ha == NULL))
		return (ret);

	if (ha->personality != ECORE_PCI_ETH_IWARP &&
		ha->personality != ECORE_PCI_ETH_ROCE)
		return (ret);

	ret = _qlnx_rdma_dev_remove(ha);

	if (ret)
		return (ret);

	mtx_lock(&qlnx_rdma_dev_lock);

	if (qlnx_host_list == ha) {
		qlnx_host_list = ha->next;
		ha->next = NULL;
		mtx_unlock(&qlnx_rdma_dev_lock);
		QL_DPRINT12(ha, "exit0 ha = %p\n", ha);
		return (ret);
	}

	ha_prev = ha_cur = qlnx_host_list;

	while ((ha_cur != ha) && (ha_cur != NULL)) {
		ha_prev = ha_cur;
		ha_cur = ha_cur->next;
	}

	if (ha_cur == ha) {
		ha_prev = ha->next;
		ha->next = NULL;
	}

	mtx_unlock(&qlnx_rdma_dev_lock);

	QL_DPRINT12(ha, "exit1 ha = %p\n", ha);
	return (ret);
}