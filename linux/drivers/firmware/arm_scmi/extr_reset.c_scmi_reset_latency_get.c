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
typedef  int u32 ;
struct scmi_reset_info {struct reset_dom_info* dom_info; } ;
struct scmi_handle {struct scmi_reset_info* reset_priv; } ;
struct reset_dom_info {int latency_us; } ;

/* Variables and functions */

__attribute__((used)) static int scmi_reset_latency_get(const struct scmi_handle *handle, u32 domain)
{
	struct scmi_reset_info *pi = handle->reset_priv;
	struct reset_dom_info *dom = pi->dom_info + domain;

	return dom->latency_us;
}