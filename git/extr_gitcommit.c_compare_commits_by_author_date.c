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
typedef  scalar_t__ timestamp_t ;
struct commit {int dummy; } ;
struct author_date_slab {int dummy; } ;

/* Variables and functions */
 scalar_t__* author_date_slab_at (struct author_date_slab*,struct commit const*) ; 

int compare_commits_by_author_date(const void *a_, const void *b_,
				   void *cb_data)
{
	const struct commit *a = a_, *b = b_;
	struct author_date_slab *author_date = cb_data;
	timestamp_t a_date = *(author_date_slab_at(author_date, a));
	timestamp_t b_date = *(author_date_slab_at(author_date, b));

	/* newer commits with larger date first */
	if (a_date < b_date)
		return 1;
	else if (a_date > b_date)
		return -1;
	return 0;
}