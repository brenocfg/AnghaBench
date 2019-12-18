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
typedef  int u16 ;
struct ena_rss {struct ena_admin_feature_rss_hash_control* hash_ctrl; } ;
struct ena_com_dev {struct ena_rss rss; } ;
struct ena_admin_feature_rss_hash_control {TYPE_2__* selected_fields; TYPE_1__* supported_fields; } ;
typedef  enum ena_admin_flow_hash_proto { ____Placeholder_ena_admin_flow_hash_proto } ena_admin_flow_hash_proto ;
struct TYPE_4__ {int fields; } ;
struct TYPE_3__ {int fields; } ;

/* Variables and functions */
 int ENA_ADMIN_RSS_PROTO_NUM ; 
 int ENA_COM_INVAL ; 
 int ena_com_get_hash_ctrl (struct ena_com_dev*,int,int /*<<< orphan*/ *) ; 
 int ena_com_set_hash_ctrl (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_trc_err (char*,int,...) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_fill_hash_ctrl(struct ena_com_dev *ena_dev,
			   enum ena_admin_flow_hash_proto proto,
			   u16 hash_fields)
{
	struct ena_rss *rss = &ena_dev->rss;
	struct ena_admin_feature_rss_hash_control *hash_ctrl = rss->hash_ctrl;
	u16 supported_fields;
	int rc;

	if (proto >= ENA_ADMIN_RSS_PROTO_NUM) {
		ena_trc_err("Invalid proto num (%u)\n", proto);
		return ENA_COM_INVAL;
	}

	/* Get the ctrl table */
	rc = ena_com_get_hash_ctrl(ena_dev, proto, NULL);
	if (unlikely(rc))
		return rc;

	/* Make sure all the fields are supported */
	supported_fields = hash_ctrl->supported_fields[proto].fields;
	if ((hash_fields & supported_fields) != hash_fields) {
		ena_trc_err("proto %d doesn't support the required fields %x. supports only: %x\n",
			    proto, hash_fields, supported_fields);
	}

	hash_ctrl->selected_fields[proto].fields = hash_fields;

	rc = ena_com_set_hash_ctrl(ena_dev);

	/* In case of failure, restore the old hash ctrl */
	if (unlikely(rc))
		ena_com_get_hash_ctrl(ena_dev, 0, NULL);

	return 0;
}