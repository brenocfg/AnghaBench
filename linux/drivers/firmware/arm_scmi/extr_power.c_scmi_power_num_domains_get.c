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
struct scmi_power_info {int num_domains; } ;
struct scmi_handle {struct scmi_power_info* power_priv; } ;

/* Variables and functions */

__attribute__((used)) static int scmi_power_num_domains_get(const struct scmi_handle *handle)
{
	struct scmi_power_info *pi = handle->power_priv;

	return pi->num_domains;
}