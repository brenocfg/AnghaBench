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
typedef  long double uint64_t ;
typedef  int /*<<< orphan*/  total_time_ts ;
typedef  int /*<<< orphan*/  total_time_bt ;
typedef  int /*<<< orphan*/  total_dma_ts ;
typedef  int /*<<< orphan*/  total_dma_bt ;
struct timespec {int tv_sec; int tv_nsec; } ;
struct ctl_io_stats {int /*<<< orphan*/ * dma_time; int /*<<< orphan*/ * time; scalar_t__* dmas; scalar_t__* operations; scalar_t__* bytes; } ;
struct bintime {int tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int CTL_STATS_NUM_TYPES ; 
 int /*<<< orphan*/  bintime2timespec (struct timespec*,struct timespec*) ; 
 int /*<<< orphan*/  bintime_add (struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bintime_sub (struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct timespec*,int) ; 

__attribute__((used)) static void
compute_stats(struct ctl_io_stats *cur_stats,
	      struct ctl_io_stats *prev_stats, long double etime,
	      long double *mbsec, long double *kb_per_transfer,
	      long double *transfers_per_second, long double *ms_per_transfer,
	      long double *ms_per_dma, long double *dmas_per_second)
{
	uint64_t total_bytes = 0, total_operations = 0, total_dmas = 0;
	struct bintime total_time_bt, total_dma_bt;
	struct timespec total_time_ts, total_dma_ts;
	int i;

	bzero(&total_time_bt, sizeof(total_time_bt));
	bzero(&total_dma_bt, sizeof(total_dma_bt));
	bzero(&total_time_ts, sizeof(total_time_ts));
	bzero(&total_dma_ts, sizeof(total_dma_ts));
	for (i = 0; i < CTL_STATS_NUM_TYPES; i++) {
		total_bytes += cur_stats->bytes[i];
		total_operations += cur_stats->operations[i];
		total_dmas += cur_stats->dmas[i];
		bintime_add(&total_time_bt, &cur_stats->time[i]);
		bintime_add(&total_dma_bt, &cur_stats->dma_time[i]);
		if (prev_stats != NULL) {
			total_bytes -= prev_stats->bytes[i];
			total_operations -= prev_stats->operations[i];
			total_dmas -= prev_stats->dmas[i];
			bintime_sub(&total_time_bt, &prev_stats->time[i]);
			bintime_sub(&total_dma_bt, &prev_stats->dma_time[i]);
		}
	}

	*mbsec = total_bytes;
	*mbsec /= 1024 * 1024;
	if (etime > 0.0)
		*mbsec /= etime;
	else
		*mbsec = 0;
	*kb_per_transfer = total_bytes;
	*kb_per_transfer /= 1024;
	if (total_operations > 0)
		*kb_per_transfer /= total_operations;
	else
		*kb_per_transfer = 0;
	*transfers_per_second = total_operations;
	*dmas_per_second = total_dmas;
	if (etime > 0.0) {
		*transfers_per_second /= etime;
		*dmas_per_second /= etime;
	} else {
		*transfers_per_second = 0;
		*dmas_per_second = 0;
	}

	bintime2timespec(&total_time_bt, &total_time_ts);
	bintime2timespec(&total_dma_bt, &total_dma_ts);
	if (total_operations > 0) {
		/*
		 * Convert the timespec to milliseconds.
		 */
		*ms_per_transfer = total_time_ts.tv_sec * 1000;
		*ms_per_transfer += total_time_ts.tv_nsec / 1000000;
		*ms_per_transfer /= total_operations;
	} else
		*ms_per_transfer = 0;

	if (total_dmas > 0) {
		/*
		 * Convert the timespec to milliseconds.
		 */
		*ms_per_dma = total_dma_ts.tv_sec * 1000;
		*ms_per_dma += total_dma_ts.tv_nsec / 1000000;
		*ms_per_dma /= total_dmas;
	} else
		*ms_per_dma = 0;
}