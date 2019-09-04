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
struct urlmatch_item {scalar_t__ hostmatch_len; scalar_t__ pathmatch_len; scalar_t__ user_matched; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_matches(const struct urlmatch_item *a,
		       const struct urlmatch_item *b)
{
	if (a->hostmatch_len != b->hostmatch_len)
		return a->hostmatch_len < b->hostmatch_len ? -1 : 1;
	if (a->pathmatch_len != b->pathmatch_len)
		return a->pathmatch_len < b->pathmatch_len ? -1 : 1;
	if (a->user_matched != b->user_matched)
		return b->user_matched ? -1 : 1;
	return 0;
}