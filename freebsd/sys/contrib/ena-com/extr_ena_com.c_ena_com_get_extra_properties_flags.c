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
struct ena_com_dev {int dummy; } ;
struct ena_admin_get_feat_resp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_EXTRA_PROPERTIES_FLAGS ; 
 int ena_com_get_feature (struct ena_com_dev*,struct ena_admin_get_feat_resp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ena_com_get_extra_properties_flags(struct ena_com_dev *ena_dev,
				       struct ena_admin_get_feat_resp *resp)
{
	return ena_com_get_feature(ena_dev, resp,
				   ENA_ADMIN_EXTRA_PROPERTIES_FLAGS, 0);
}