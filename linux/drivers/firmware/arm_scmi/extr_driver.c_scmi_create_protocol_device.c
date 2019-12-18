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
struct scmi_info {int /*<<< orphan*/  dev; } ;
struct scmi_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct scmi_device* scmi_device_create (struct device_node*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scmi_device_destroy (struct scmi_device*) ; 
 scalar_t__ scmi_mbox_txrx_setup (struct scmi_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scmi_set_handle (struct scmi_device*) ; 

__attribute__((used)) static inline void
scmi_create_protocol_device(struct device_node *np, struct scmi_info *info,
			    int prot_id)
{
	struct scmi_device *sdev;

	sdev = scmi_device_create(np, info->dev, prot_id);
	if (!sdev) {
		dev_err(info->dev, "failed to create %d protocol device\n",
			prot_id);
		return;
	}

	if (scmi_mbox_txrx_setup(info, &sdev->dev, prot_id)) {
		dev_err(&sdev->dev, "failed to setup transport\n");
		scmi_device_destroy(sdev);
		return;
	}

	/* setup handle now as the transport is ready */
	scmi_set_handle(sdev);
}