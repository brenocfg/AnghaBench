#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct devfreq_dev_profile {int max_state; unsigned long* freq_table; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct devfreq {TYPE_1__ dev; struct devfreq_dev_profile* profile; } ;
struct dev_pm_opp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dev_pm_opp*) ; 
 int PTR_ERR (struct dev_pm_opp*) ; 
 struct dev_pm_opp* dev_pm_opp_find_freq_ceil (int /*<<< orphan*/ ,unsigned long*) ; 
 int dev_pm_opp_get_opp_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 
 unsigned long* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int set_freq_table(struct devfreq *devfreq)
{
	struct devfreq_dev_profile *profile = devfreq->profile;
	struct dev_pm_opp *opp;
	unsigned long freq;
	int i, count;

	/* Initialize the freq_table from OPP table */
	count = dev_pm_opp_get_opp_count(devfreq->dev.parent);
	if (count <= 0)
		return -EINVAL;

	profile->max_state = count;
	profile->freq_table = devm_kcalloc(devfreq->dev.parent,
					profile->max_state,
					sizeof(*profile->freq_table),
					GFP_KERNEL);
	if (!profile->freq_table) {
		profile->max_state = 0;
		return -ENOMEM;
	}

	for (i = 0, freq = 0; i < profile->max_state; i++, freq++) {
		opp = dev_pm_opp_find_freq_ceil(devfreq->dev.parent, &freq);
		if (IS_ERR(opp)) {
			devm_kfree(devfreq->dev.parent, profile->freq_table);
			profile->max_state = 0;
			return PTR_ERR(opp);
		}
		dev_pm_opp_put(opp);
		profile->freq_table[i] = freq;
	}

	return 0;
}