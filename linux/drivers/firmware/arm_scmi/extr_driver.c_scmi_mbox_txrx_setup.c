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
struct scmi_info {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int scmi_mbox_chan_setup (struct scmi_info*,struct device*,int,int) ; 

__attribute__((used)) static inline int
scmi_mbox_txrx_setup(struct scmi_info *info, struct device *dev, int prot_id)
{
	int ret = scmi_mbox_chan_setup(info, dev, prot_id, true);

	if (!ret) /* Rx is optional, hence no error check */
		scmi_mbox_chan_setup(info, dev, prot_id, false);

	return ret;
}