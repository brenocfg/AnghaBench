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
struct cache_def {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lstat_cache_matchlen (struct cache_def*,char const*,int,int*,int,int) ; 

__attribute__((used)) static int lstat_cache(struct cache_def *cache, const char *name, int len,
		       int track_flags, int prefix_len_stat_func)
{
	int flags;
	(void)lstat_cache_matchlen(cache, name, len, &flags, track_flags,
			prefix_len_stat_func);
	return flags;
}