#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int num_qps; int num_srqs; int min_dpis; int /*<<< orphan*/  rdma_protocol; void* gl_pi; scalar_t__ roce_edpm_mode; } ;
struct TYPE_7__ {int num_cons; } ;
struct ecore_pf_params {TYPE_2__ rdma_pf_params; TYPE_1__ eth_pf_params; } ;
struct ecore_dev {int rx_coalesce_usecs; int tx_coalesce_usecs; int /*<<< orphan*/  int_coalescing_mode; int /*<<< orphan*/  int_mode; } ;
struct TYPE_9__ {int num_rss; int num_tc; scalar_t__ personality; int rx_coalesce_usecs; int tx_coalesce_usecs; struct ecore_dev cdev; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_3__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_COAL_MODE_ENABLE ; 
 int /*<<< orphan*/  ECORE_INT_MODE_MSIX ; 
 scalar_t__ ECORE_PCI_ETH_IWARP ; 
 scalar_t__ ECORE_PCI_ETH_ROCE ; 
 int /*<<< orphan*/  ECORE_RDMA_PROTOCOL_IWARP ; 
 int /*<<< orphan*/  ECORE_RDMA_PROTOCOL_ROCE ; 
 void* ECORE_ROCE_PROTOCOL_INDEX ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct ecore_pf_params*,int /*<<< orphan*/ ,int) ; 
 int qlnx_nic_setup (struct ecore_dev*,struct ecore_pf_params*) ; 
 int qlnx_nic_start (struct ecore_dev*) ; 
 int /*<<< orphan*/  qlnx_set_lldp_tlvx (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ qlnx_vf_device (TYPE_3__*) ; 

__attribute__((used)) static int
qlnx_slowpath_start(qlnx_host_t *ha)
{
	struct ecore_dev	*cdev;
	struct ecore_pf_params	pf_params;
	int			rc;

	memset(&pf_params, 0, sizeof(struct ecore_pf_params));
	pf_params.eth_pf_params.num_cons  =
		(ha->num_rss) * (ha->num_tc + 1);

#ifdef QLNX_ENABLE_IWARP
	if (qlnx_vf_device(ha) != 0) {
		if(ha->personality == ECORE_PCI_ETH_IWARP) {
			device_printf(ha->pci_dev, "setting parameters required by iWARP dev\n");	
			pf_params.rdma_pf_params.num_qps = 1024;
			pf_params.rdma_pf_params.num_srqs = 1024;
			pf_params.rdma_pf_params.gl_pi = ECORE_ROCE_PROTOCOL_INDEX;
			pf_params.rdma_pf_params.rdma_protocol = ECORE_RDMA_PROTOCOL_IWARP;
		} else if(ha->personality == ECORE_PCI_ETH_ROCE) {
			device_printf(ha->pci_dev, "setting parameters required by RoCE dev\n");	
			pf_params.rdma_pf_params.num_qps = 8192;
			pf_params.rdma_pf_params.num_srqs = 8192;
			//pf_params.rdma_pf_params.min_dpis = 0;
			pf_params.rdma_pf_params.min_dpis = 8;
			pf_params.rdma_pf_params.roce_edpm_mode = 0;
			pf_params.rdma_pf_params.gl_pi = ECORE_ROCE_PROTOCOL_INDEX;
			pf_params.rdma_pf_params.rdma_protocol = ECORE_RDMA_PROTOCOL_ROCE;
		}
	}
#endif /* #ifdef QLNX_ENABLE_IWARP */

	cdev = &ha->cdev;

	rc = qlnx_nic_setup(cdev, &pf_params);
        if (rc)
                goto qlnx_slowpath_start_exit;

        cdev->int_mode = ECORE_INT_MODE_MSIX;
        cdev->int_coalescing_mode = ECORE_COAL_MODE_ENABLE;

#ifdef QLNX_MAX_COALESCE
	cdev->rx_coalesce_usecs = 255;
	cdev->tx_coalesce_usecs = 255;
#endif

	rc = qlnx_nic_start(cdev);

	ha->rx_coalesce_usecs = cdev->rx_coalesce_usecs;
	ha->tx_coalesce_usecs = cdev->tx_coalesce_usecs;

#ifdef QLNX_USER_LLDP
	(void)qlnx_set_lldp_tlvx(ha, NULL);
#endif /* #ifdef QLNX_USER_LLDP */

qlnx_slowpath_start_exit:

	return (rc);
}