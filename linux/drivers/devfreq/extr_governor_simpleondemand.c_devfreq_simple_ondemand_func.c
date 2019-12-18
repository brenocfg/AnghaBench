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
struct devfreq_simple_ondemand_data {int upthreshold; int downdifferential; } ;
struct devfreq_dev_status {int total_time; int busy_time; unsigned long current_frequency; } ;
struct devfreq {struct devfreq_dev_status last_status; struct devfreq_simple_ondemand_data* data; } ;

/* Variables and functions */
 unsigned long DEVFREQ_MAX_FREQ ; 
 unsigned int DFSO_DOWNDIFFERENCTIAL ; 
 unsigned int DFSO_UPTHRESHOLD ; 
 int EINVAL ; 
 int devfreq_update_stats (struct devfreq*) ; 
 unsigned long long div_u64 (unsigned long long,unsigned int) ; 

__attribute__((used)) static int devfreq_simple_ondemand_func(struct devfreq *df,
					unsigned long *freq)
{
	int err;
	struct devfreq_dev_status *stat;
	unsigned long long a, b;
	unsigned int dfso_upthreshold = DFSO_UPTHRESHOLD;
	unsigned int dfso_downdifferential = DFSO_DOWNDIFFERENCTIAL;
	struct devfreq_simple_ondemand_data *data = df->data;

	err = devfreq_update_stats(df);
	if (err)
		return err;

	stat = &df->last_status;

	if (data) {
		if (data->upthreshold)
			dfso_upthreshold = data->upthreshold;
		if (data->downdifferential)
			dfso_downdifferential = data->downdifferential;
	}
	if (dfso_upthreshold > 100 ||
	    dfso_upthreshold < dfso_downdifferential)
		return -EINVAL;

	/* Assume MAX if it is going to be divided by zero */
	if (stat->total_time == 0) {
		*freq = DEVFREQ_MAX_FREQ;
		return 0;
	}

	/* Prevent overflow */
	if (stat->busy_time >= (1 << 24) || stat->total_time >= (1 << 24)) {
		stat->busy_time >>= 7;
		stat->total_time >>= 7;
	}

	/* Set MAX if it's busy enough */
	if (stat->busy_time * 100 >
	    stat->total_time * dfso_upthreshold) {
		*freq = DEVFREQ_MAX_FREQ;
		return 0;
	}

	/* Set MAX if we do not know the initial frequency */
	if (stat->current_frequency == 0) {
		*freq = DEVFREQ_MAX_FREQ;
		return 0;
	}

	/* Keep the current frequency */
	if (stat->busy_time * 100 >
	    stat->total_time * (dfso_upthreshold - dfso_downdifferential)) {
		*freq = stat->current_frequency;
		return 0;
	}

	/* Set the desired frequency based on the load */
	a = stat->busy_time;
	a *= stat->current_frequency;
	b = div_u64(a, stat->total_time);
	b *= 100;
	b = div_u64(b, (dfso_upthreshold - dfso_downdifferential / 2));
	*freq = (unsigned long) b;

	return 0;
}