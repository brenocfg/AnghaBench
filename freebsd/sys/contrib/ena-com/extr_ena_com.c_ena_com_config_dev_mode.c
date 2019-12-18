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
struct ena_llq_configurations {int dummy; } ;
struct ena_eth_io_tx_desc {int dummy; } ;
struct TYPE_2__ {int descs_num_before_header; int desc_list_entry_size; } ;
struct ena_com_dev {int tx_max_header_size; int /*<<< orphan*/  tx_mem_queue_type; TYPE_1__ llq_info; } ;
struct ena_admin_feature_llq_desc {int /*<<< orphan*/  max_llq_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_PLACEMENT_POLICY_DEV ; 
 int /*<<< orphan*/  ENA_ADMIN_PLACEMENT_POLICY_HOST ; 
 int ENA_COM_INVAL ; 
 int ena_com_config_llq_info (struct ena_com_dev*,struct ena_admin_feature_llq_desc*,struct ena_llq_configurations*) ; 
 int /*<<< orphan*/  ena_trc_err (char*) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_config_dev_mode(struct ena_com_dev *ena_dev,
			    struct ena_admin_feature_llq_desc *llq_features,
			    struct ena_llq_configurations *llq_default_cfg)
{
	int rc;
	int size;

	if (!llq_features->max_llq_num) {
		ena_dev->tx_mem_queue_type = ENA_ADMIN_PLACEMENT_POLICY_HOST;
		return 0;
	}

	rc = ena_com_config_llq_info(ena_dev, llq_features, llq_default_cfg);
	if (rc)
		return rc;

	/* Validate the descriptor is not too big */
	size = ena_dev->tx_max_header_size;
	size += ena_dev->llq_info.descs_num_before_header *
		sizeof(struct ena_eth_io_tx_desc);

	if (unlikely(ena_dev->llq_info.desc_list_entry_size < size)) {
		ena_trc_err("the size of the LLQ entry is smaller than needed\n");
		return ENA_COM_INVAL;
	}

	ena_dev->tx_mem_queue_type = ENA_ADMIN_PLACEMENT_POLICY_DEV;

	return 0;
}