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
typedef  scalar_t__ time_t ;
struct rate_data {scalar_t__* timestamp; int* qps; } ;

/* Variables and functions */
 int RATE_WINDOW ; 

__attribute__((used)) static int* infra_rate_find_second(void* data, time_t t)
{
	struct rate_data* d = (struct rate_data*)data;
	int i, oldest;
	for(i=0; i<RATE_WINDOW; i++) {
		if(d->timestamp[i] == t)
			return &(d->qps[i]);
	}
	/* remove oldest timestamp, and insert it at t with 0 qps */
	oldest = 0;
	for(i=0; i<RATE_WINDOW; i++) {
		if(d->timestamp[i] < d->timestamp[oldest])
			oldest = i;
	}
	d->timestamp[oldest] = t;
	d->qps[oldest] = 0;
	return &(d->qps[oldest]);
}