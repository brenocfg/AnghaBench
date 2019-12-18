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
typedef  int time_t ;
struct rate_data {int* timestamp; int* qps; } ;

/* Variables and functions */
 int RATE_WINDOW ; 

int infra_rate_max(void* data, time_t now)
{
	struct rate_data* d = (struct rate_data*)data;
	int i, max = 0;
	for(i=0; i<RATE_WINDOW; i++) {
		if(now-d->timestamp[i] <= RATE_WINDOW) {
			if(d->qps[i] > max)
				max = d->qps[i];
		}
	}
	return max;
}