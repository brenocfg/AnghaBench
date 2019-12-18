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
struct edac_device_ctl_info {int log_ue; } ;

/* Variables and functions */

__attribute__((used)) static inline int edac_device_get_log_ue(struct edac_device_ctl_info *edac_dev)
{
	return edac_dev->log_ue;
}