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
struct scmi_perf_info {struct perf_dom_info* dom_info; } ;
struct scmi_opp {unsigned long perf; } ;
struct scmi_handle {struct scmi_perf_info* perf_priv; } ;
struct perf_dom_info {int opp_count; unsigned long mult_factor; struct scmi_opp* opp; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int dev_pm_opp_add (struct device*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_opp_remove (struct device*,unsigned long) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,unsigned long) ; 
 int scmi_dev_domain_id (struct device*) ; 

__attribute__((used)) static int scmi_dvfs_device_opps_add(const struct scmi_handle *handle,
				     struct device *dev)
{
	int idx, ret, domain;
	unsigned long freq;
	struct scmi_opp *opp;
	struct perf_dom_info *dom;
	struct scmi_perf_info *pi = handle->perf_priv;

	domain = scmi_dev_domain_id(dev);
	if (domain < 0)
		return domain;

	dom = pi->dom_info + domain;

	for (opp = dom->opp, idx = 0; idx < dom->opp_count; idx++, opp++) {
		freq = opp->perf * dom->mult_factor;

		ret = dev_pm_opp_add(dev, freq, 0);
		if (ret) {
			dev_warn(dev, "failed to add opp %luHz\n", freq);

			while (idx-- > 0) {
				freq = (--opp)->perf * dom->mult_factor;
				dev_pm_opp_remove(dev, freq);
			}
			return ret;
		}
	}
	return 0;
}