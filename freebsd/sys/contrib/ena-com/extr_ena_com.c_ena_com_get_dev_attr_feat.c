#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ena_com_dev_get_features_ctx {int /*<<< orphan*/  ind_table; int /*<<< orphan*/  llq; int /*<<< orphan*/  hw_hints; int /*<<< orphan*/  offload; int /*<<< orphan*/  aenq; int /*<<< orphan*/  max_queues; int /*<<< orphan*/  max_queue_ext; int /*<<< orphan*/  dev_attr; } ;
struct ena_com_dev {int supported_features; int /*<<< orphan*/  tx_max_header_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_tx_header_size; } ;
struct TYPE_6__ {int supported_features; scalar_t__ version; int /*<<< orphan*/  max_header_size; TYPE_1__ max_queue_ext; } ;
struct TYPE_5__ {TYPE_3__ ind_table; TYPE_3__ llq; TYPE_3__ hw_hints; TYPE_3__ offload; TYPE_3__ aenq; TYPE_3__ max_queue; TYPE_3__ max_queue_ext; TYPE_3__ dev_attr; } ;
struct ena_admin_get_feat_resp {TYPE_2__ u; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ENA_ADMIN_AENQ_CONFIG ; 
 int /*<<< orphan*/  ENA_ADMIN_DEVICE_ATTRIBUTES ; 
 int /*<<< orphan*/  ENA_ADMIN_HW_HINTS ; 
 int /*<<< orphan*/  ENA_ADMIN_LLQ ; 
 int /*<<< orphan*/  ENA_ADMIN_MAX_QUEUES_EXT ; 
 int /*<<< orphan*/  ENA_ADMIN_MAX_QUEUES_NUM ; 
 int /*<<< orphan*/  ENA_ADMIN_RSS_REDIRECTION_TABLE_CONFIG ; 
 int /*<<< orphan*/  ENA_ADMIN_STATELESS_OFFLOAD_CONFIG ; 
 int ENA_COM_UNSUPPORTED ; 
 scalar_t__ ENA_FEATURE_MAX_QUEUE_EXT_VER ; 
 int ena_com_get_feature (struct ena_com_dev*,struct ena_admin_get_feat_resp*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

int ena_com_get_dev_attr_feat(struct ena_com_dev *ena_dev,
			      struct ena_com_dev_get_features_ctx *get_feat_ctx)
{
	struct ena_admin_get_feat_resp get_resp;
	int rc;

	rc = ena_com_get_feature(ena_dev, &get_resp,
				 ENA_ADMIN_DEVICE_ATTRIBUTES, 0);
	if (rc)
		return rc;

	memcpy(&get_feat_ctx->dev_attr, &get_resp.u.dev_attr,
	       sizeof(get_resp.u.dev_attr));
	ena_dev->supported_features = get_resp.u.dev_attr.supported_features;

	if (ena_dev->supported_features & BIT(ENA_ADMIN_MAX_QUEUES_EXT)) {
		rc = ena_com_get_feature(ena_dev, &get_resp,
					 ENA_ADMIN_MAX_QUEUES_EXT,
					 ENA_FEATURE_MAX_QUEUE_EXT_VER);
		if (rc)
			return rc;

		if (get_resp.u.max_queue_ext.version != ENA_FEATURE_MAX_QUEUE_EXT_VER)
			return -EINVAL;

		memcpy(&get_feat_ctx->max_queue_ext, &get_resp.u.max_queue_ext,
		       sizeof(get_resp.u.max_queue_ext));
		ena_dev->tx_max_header_size =
			get_resp.u.max_queue_ext.max_queue_ext.max_tx_header_size;
	} else {
		rc = ena_com_get_feature(ena_dev, &get_resp,
					 ENA_ADMIN_MAX_QUEUES_NUM, 0);
		memcpy(&get_feat_ctx->max_queues, &get_resp.u.max_queue,
		       sizeof(get_resp.u.max_queue));
		ena_dev->tx_max_header_size =
			get_resp.u.max_queue.max_header_size;

		if (rc)
			return rc;
	}

	rc = ena_com_get_feature(ena_dev, &get_resp,
				 ENA_ADMIN_AENQ_CONFIG, 0);
	if (rc)
		return rc;

	memcpy(&get_feat_ctx->aenq, &get_resp.u.aenq,
	       sizeof(get_resp.u.aenq));

	rc = ena_com_get_feature(ena_dev, &get_resp,
				 ENA_ADMIN_STATELESS_OFFLOAD_CONFIG, 0);
	if (rc)
		return rc;

	memcpy(&get_feat_ctx->offload, &get_resp.u.offload,
	       sizeof(get_resp.u.offload));

	/* Driver hints isn't mandatory admin command. So in case the
	 * command isn't supported set driver hints to 0
	 */
	rc = ena_com_get_feature(ena_dev, &get_resp, ENA_ADMIN_HW_HINTS, 0);

	if (!rc)
		memcpy(&get_feat_ctx->hw_hints, &get_resp.u.hw_hints,
		       sizeof(get_resp.u.hw_hints));
	else if (rc == ENA_COM_UNSUPPORTED)
		memset(&get_feat_ctx->hw_hints, 0x0, sizeof(get_feat_ctx->hw_hints));
	else
		return rc;

	rc = ena_com_get_feature(ena_dev, &get_resp, ENA_ADMIN_LLQ, 0);
	if (!rc)
		memcpy(&get_feat_ctx->llq, &get_resp.u.llq,
		       sizeof(get_resp.u.llq));
	else if (rc == ENA_COM_UNSUPPORTED)
		memset(&get_feat_ctx->llq, 0x0, sizeof(get_feat_ctx->llq));
	else
		return rc;

	rc = ena_com_get_feature(ena_dev, &get_resp,
				 ENA_ADMIN_RSS_REDIRECTION_TABLE_CONFIG, 0);
	if (!rc)
		memcpy(&get_feat_ctx->ind_table, &get_resp.u.ind_table,
		       sizeof(get_resp.u.ind_table));
	else if (rc == ENA_COM_UNSUPPORTED)
		memset(&get_feat_ctx->ind_table, 0x0,
		       sizeof(get_feat_ctx->ind_table));
	else
		return rc;

	return 0;
}