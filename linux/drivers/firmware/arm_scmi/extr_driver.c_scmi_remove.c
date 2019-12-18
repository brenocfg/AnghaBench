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
struct idr {int dummy; } ;
struct scmi_info {struct idr rx_idr; struct idr tx_idr; int /*<<< orphan*/  node; scalar_t__ users; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  idr_destroy (struct idr*) ; 
 int idr_for_each (struct idr*,int /*<<< orphan*/ ,struct idr*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct scmi_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  scmi_list_mutex ; 
 int /*<<< orphan*/  scmi_mbox_free_channel ; 

__attribute__((used)) static int scmi_remove(struct platform_device *pdev)
{
	int ret = 0;
	struct scmi_info *info = platform_get_drvdata(pdev);
	struct idr *idr = &info->tx_idr;

	mutex_lock(&scmi_list_mutex);
	if (info->users)
		ret = -EBUSY;
	else
		list_del(&info->node);
	mutex_unlock(&scmi_list_mutex);

	if (ret)
		return ret;

	/* Safe to free channels since no more users */
	ret = idr_for_each(idr, scmi_mbox_free_channel, idr);
	idr_destroy(&info->tx_idr);

	idr = &info->rx_idr;
	ret = idr_for_each(idr, scmi_mbox_free_channel, idr);
	idr_destroy(&info->rx_idr);

	return ret;
}