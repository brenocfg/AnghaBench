#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ timestamp_t ;
struct commit_list {TYPE_1__* item; } ;
struct commit {int dummy; } ;
struct TYPE_2__ {scalar_t__ date; } ;

/* Variables and functions */
 int SLOP ; 
 int /*<<< orphan*/  everybody_uninteresting (struct commit_list*,struct commit**) ; 

__attribute__((used)) static int still_interesting(struct commit_list *src, timestamp_t date, int slop,
			     struct commit **interesting_cache)
{
	/*
	 * No source list at all? We're definitely done..
	 */
	if (!src)
		return 0;

	/*
	 * Does the destination list contain entries with a date
	 * before the source list? Definitely _not_ done.
	 */
	if (date <= src->item->date)
		return SLOP;

	/*
	 * Does the source list still have interesting commits in
	 * it? Definitely not done..
	 */
	if (!everybody_uninteresting(src, interesting_cache))
		return SLOP;

	/* Ok, we're closing in.. */
	return slop-1;
}