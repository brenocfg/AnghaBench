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
struct rev_name {int from_tag; scalar_t__ taggerdate; int distance; } ;

/* Variables and functions */

__attribute__((used)) static int is_better_name(struct rev_name *name,
			  const char *tip_name,
			  timestamp_t taggerdate,
			  int generation,
			  int distance,
			  int from_tag)
{
	/*
	 * When comparing names based on tags, prefer names
	 * based on the older tag, even if it is farther away.
	 */
	if (from_tag && name->from_tag)
		return (name->taggerdate > taggerdate ||
			(name->taggerdate == taggerdate &&
			 name->distance > distance));

	/*
	 * We know that at least one of them is a non-tag at this point.
	 * favor a tag over a non-tag.
	 */
	if (name->from_tag != from_tag)
		return from_tag;

	/*
	 * We are now looking at two non-tags.  Tiebreak to favor
	 * shorter hops.
	 */
	if (name->distance != distance)
		return name->distance > distance;

	/* ... or tiebreak to favor older date */
	if (name->taggerdate != taggerdate)
		return name->taggerdate > taggerdate;

	/* keep the current one if we cannot decide */
	return 0;
}