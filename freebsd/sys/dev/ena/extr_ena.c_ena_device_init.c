#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int supported_groups; } ;
struct ena_com_dev_get_features_ctx {TYPE_1__ aenq; } ;
struct ena_com_dev {int dummy; } ;
struct ena_adapter {int dma_width; struct ena_com_dev* ena_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENA_ADMIN_FATAL_ERROR ; 
 int /*<<< orphan*/  ENA_ADMIN_KEEP_ALIVE ; 
 int /*<<< orphan*/  ENA_ADMIN_LINK_CHANGE ; 
 int /*<<< orphan*/  ENA_ADMIN_NOTIFICATION ; 
 int /*<<< orphan*/  ENA_ADMIN_WARNING ; 
 int ENA_MMIO_DISABLE_REG_READ ; 
 int /*<<< orphan*/  ENA_REGS_RESET_NORMAL ; 
 int /*<<< orphan*/  aenq_handlers ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ena_com_admin_destroy (struct ena_com_dev*) ; 
 int ena_com_admin_init (struct ena_com_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ena_com_delete_host_info (struct ena_com_dev*) ; 
 int ena_com_dev_reset (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int ena_com_get_dev_attr_feat (struct ena_com_dev*,struct ena_com_dev_get_features_ctx*) ; 
 int ena_com_get_dma_width (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_mmio_reg_read_request_destroy (struct ena_com_dev*) ; 
 int ena_com_mmio_reg_read_request_init (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_set_admin_polling_mode (struct ena_com_dev*,int) ; 
 int ena_com_set_aenq_config (struct ena_com_dev*,int) ; 
 int /*<<< orphan*/  ena_com_set_mmio_read_mode (struct ena_com_dev*,int) ; 
 int ena_com_validate_version (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_config_host_info (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int pci_get_revid (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ena_device_init(struct ena_adapter *adapter, device_t pdev,
    struct ena_com_dev_get_features_ctx *get_feat_ctx, int *wd_active)
{
	struct ena_com_dev* ena_dev = adapter->ena_dev;
	bool readless_supported;
	uint32_t aenq_groups;
	int dma_width;
	int rc;

	rc = ena_com_mmio_reg_read_request_init(ena_dev);
	if (unlikely(rc != 0)) {
		device_printf(pdev, "failed to init mmio read less\n");
		return (rc);
	}

	/*
	 * The PCIe configuration space revision id indicate if mmio reg
	 * read is disabled
	 */
	readless_supported = !(pci_get_revid(pdev) & ENA_MMIO_DISABLE_REG_READ);
	ena_com_set_mmio_read_mode(ena_dev, readless_supported);

	rc = ena_com_dev_reset(ena_dev, ENA_REGS_RESET_NORMAL);
	if (unlikely(rc != 0)) {
		device_printf(pdev, "Can not reset device\n");
		goto err_mmio_read_less;
	}

	rc = ena_com_validate_version(ena_dev);
	if (unlikely(rc != 0)) {
		device_printf(pdev, "device version is too low\n");
		goto err_mmio_read_less;
	}

	dma_width = ena_com_get_dma_width(ena_dev);
	if (unlikely(dma_width < 0)) {
		device_printf(pdev, "Invalid dma width value %d", dma_width);
		rc = dma_width;
		goto err_mmio_read_less;
	}
	adapter->dma_width = dma_width;

	/* ENA admin level init */
	rc = ena_com_admin_init(ena_dev, &aenq_handlers);
	if (unlikely(rc != 0)) {
		device_printf(pdev,
		    "Can not initialize ena admin queue with device\n");
		goto err_mmio_read_less;
	}

	/*
	 * To enable the msix interrupts the driver needs to know the number
	 * of queues. So the driver uses polling mode to retrieve this
	 * information
	 */
	ena_com_set_admin_polling_mode(ena_dev, true);

	ena_config_host_info(ena_dev, pdev);

	/* Get Device Attributes */
	rc = ena_com_get_dev_attr_feat(ena_dev, get_feat_ctx);
	if (unlikely(rc != 0)) {
		device_printf(pdev,
		    "Cannot get attribute for ena device rc: %d\n", rc);
		goto err_admin_init;
	}

	aenq_groups = BIT(ENA_ADMIN_LINK_CHANGE) |
	    BIT(ENA_ADMIN_FATAL_ERROR) |
	    BIT(ENA_ADMIN_WARNING) |
	    BIT(ENA_ADMIN_NOTIFICATION) |
	    BIT(ENA_ADMIN_KEEP_ALIVE);

	aenq_groups &= get_feat_ctx->aenq.supported_groups;
	rc = ena_com_set_aenq_config(ena_dev, aenq_groups);
	if (unlikely(rc != 0)) {
		device_printf(pdev, "Cannot configure aenq groups rc: %d\n", rc);
		goto err_admin_init;
	}

	*wd_active = !!(aenq_groups & BIT(ENA_ADMIN_KEEP_ALIVE));

	return (0);

err_admin_init:
	ena_com_delete_host_info(ena_dev);
	ena_com_admin_destroy(ena_dev);
err_mmio_read_less:
	ena_com_mmio_reg_read_request_destroy(ena_dev);

	return (rc);
}