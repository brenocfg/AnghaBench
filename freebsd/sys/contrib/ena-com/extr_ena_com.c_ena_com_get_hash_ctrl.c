#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ena_rss {TYPE_2__* hash_ctrl; int /*<<< orphan*/  hash_ctrl_dma_addr; } ;
struct ena_com_dev {struct ena_rss rss; } ;
struct ena_admin_get_feat_resp {int dummy; } ;
typedef  enum ena_admin_flow_hash_proto { ____Placeholder_ena_admin_flow_hash_proto } ena_admin_flow_hash_proto ;
struct TYPE_4__ {TYPE_1__* selected_fields; } ;
struct TYPE_3__ {int /*<<< orphan*/  fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_RSS_HASH_INPUT ; 
 int ena_com_get_feature_ex (struct ena_com_dev*,struct ena_admin_get_feat_resp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_get_hash_ctrl(struct ena_com_dev *ena_dev,
			  enum ena_admin_flow_hash_proto proto,
			  u16 *fields)
{
	struct ena_rss *rss = &ena_dev->rss;
	struct ena_admin_get_feat_resp get_resp;
	int rc;

	rc = ena_com_get_feature_ex(ena_dev, &get_resp,
				    ENA_ADMIN_RSS_HASH_INPUT,
				    rss->hash_ctrl_dma_addr,
				    sizeof(*rss->hash_ctrl), 0);
	if (unlikely(rc))
		return rc;

	if (fields)
		*fields = rss->hash_ctrl->selected_fields[proto].fields;

	return 0;
}