#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timehist {size_t num; TYPE_3__* buckets; } ;
struct TYPE_5__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_4__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_6__ {scalar_t__ count; TYPE_2__ upper; TYPE_1__ lower; } ;

/* Variables and functions */
 scalar_t__ timehist_count (struct timehist*) ; 

double 
timehist_quartile(struct timehist* hist, double q)
{
	double lookfor, passed, res;
	double low = 0, up = 0;
	size_t i;
	if(!hist || hist->num == 0)
		return 0.;
	/* look for i'th element, interpolated */
	lookfor = (double)timehist_count(hist);
	if(lookfor < 4)
		return 0.; /* not enough elements for a good estimate */
	lookfor *= q;
	passed = 0;
	i = 0;
	while(i+1 < hist->num && 
		passed+(double)hist->buckets[i].count < lookfor) {
		passed += (double)hist->buckets[i++].count;
	}
	/* got the right bucket */
#ifndef S_SPLINT_S
	low = (double)hist->buckets[i].lower.tv_sec + 
		(double)hist->buckets[i].lower.tv_usec/1000000.;
	up = (double)hist->buckets[i].upper.tv_sec + 
		(double)hist->buckets[i].upper.tv_usec/1000000.;
#endif
	res = (lookfor - passed)*(up-low)/((double)hist->buckets[i].count);
	return low+res;
}