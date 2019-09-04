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
struct diff_score {int dummy; } ;

/* Variables and functions */
 int NUM_CANDIDATE_PER_DST ; 
 scalar_t__ score_compare (struct diff_score*,struct diff_score*) ; 

__attribute__((used)) static void record_if_better(struct diff_score m[], struct diff_score *o)
{
	int i, worst;

	/* find the worst one */
	worst = 0;
	for (i = 1; i < NUM_CANDIDATE_PER_DST; i++)
		if (score_compare(&m[i], &m[worst]) > 0)
			worst = i;

	/* is it better than the worst one? */
	if (score_compare(&m[worst], o) > 0)
		m[worst] = *o;
}