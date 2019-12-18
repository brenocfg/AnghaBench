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
struct timehist {int num; struct th_buck* buckets; } ;
struct th_buck {int dummy; } ;

/* Variables and functions */
 int NUM_BUCKETS_HIST ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  dosetup (struct timehist*) ; 
 int /*<<< orphan*/  free (struct timehist*) ; 

struct timehist* timehist_setup(void)
{
	struct timehist* hist = (struct timehist*)calloc(1, 
		sizeof(struct timehist));
	if(!hist)
		return NULL;
	hist->num = NUM_BUCKETS_HIST;
	hist->buckets = (struct th_buck*)calloc(hist->num, 
		sizeof(struct th_buck));
	if(!hist->buckets) {
		free(hist);
		return NULL;
	}
	/* setup the buckets */
	dosetup(hist);
	return hist;
}