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
typedef  int /*<<< orphan*/  timestamp_t ;
struct rev_info {scalar_t__ reflog_info; } ;
struct commit {int /*<<< orphan*/  date; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_reflog_timestamp (scalar_t__) ; 

__attribute__((used)) static timestamp_t comparison_date(const struct rev_info *revs,
				   struct commit *commit)
{
	return revs->reflog_info ?
		get_reflog_timestamp(revs->reflog_info) :
		commit->date;
}