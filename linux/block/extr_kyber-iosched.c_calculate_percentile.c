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
struct kyber_queue_data {unsigned int*** latency_buckets; int /*<<< orphan*/  q; scalar_t__* latency_timeout; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 scalar_t__ HZ ; 
 unsigned int KYBER_LATENCY_BUCKETS ; 
 int KYBER_LATENCY_SHIFT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/ * kyber_domain_names ; 
 int /*<<< orphan*/ * kyber_latency_type_names ; 
 scalar_t__ max (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_is_after_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  trace_kyber_latency (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int,unsigned int) ; 

__attribute__((used)) static int calculate_percentile(struct kyber_queue_data *kqd,
				unsigned int sched_domain, unsigned int type,
				unsigned int percentile)
{
	unsigned int *buckets = kqd->latency_buckets[sched_domain][type];
	unsigned int bucket, samples = 0, percentile_samples;

	for (bucket = 0; bucket < KYBER_LATENCY_BUCKETS; bucket++)
		samples += buckets[bucket];

	if (!samples)
		return -1;

	/*
	 * We do the calculation once we have 500 samples or one second passes
	 * since the first sample was recorded, whichever comes first.
	 */
	if (!kqd->latency_timeout[sched_domain])
		kqd->latency_timeout[sched_domain] = max(jiffies + HZ, 1UL);
	if (samples < 500 &&
	    time_is_after_jiffies(kqd->latency_timeout[sched_domain])) {
		return -1;
	}
	kqd->latency_timeout[sched_domain] = 0;

	percentile_samples = DIV_ROUND_UP(samples * percentile, 100);
	for (bucket = 0; bucket < KYBER_LATENCY_BUCKETS - 1; bucket++) {
		if (buckets[bucket] >= percentile_samples)
			break;
		percentile_samples -= buckets[bucket];
	}
	memset(buckets, 0, sizeof(kqd->latency_buckets[sched_domain][type]));

	trace_kyber_latency(kqd->q, kyber_domain_names[sched_domain],
			    kyber_latency_type_names[type], percentile,
			    bucket + 1, 1 << KYBER_LATENCY_SHIFT, samples);

	return bucket;
}