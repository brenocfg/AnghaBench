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
struct scmi_perf_info {struct perf_dom_info* dom_info; } ;
struct scmi_opp {unsigned long perf; unsigned long power; } ;
struct scmi_handle {struct scmi_perf_info* perf_priv; } ;
struct perf_dom_info {int opp_count; unsigned long mult_factor; struct scmi_opp* opp; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 

__attribute__((used)) static int scmi_dvfs_est_power_get(const struct scmi_handle *handle, u32 domain,
				   unsigned long *freq, unsigned long *power)
{
	struct scmi_perf_info *pi = handle->perf_priv;
	struct perf_dom_info *dom;
	unsigned long opp_freq;
	int idx, ret = -EINVAL;
	struct scmi_opp *opp;

	dom = pi->dom_info + domain;
	if (!dom)
		return -EIO;

	for (opp = dom->opp, idx = 0; idx < dom->opp_count; idx++, opp++) {
		opp_freq = opp->perf * dom->mult_factor;
		if (opp_freq < *freq)
			continue;

		*freq = opp_freq;
		*power = opp->power;
		ret = 0;
		break;
	}

	return ret;
}