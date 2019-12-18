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
struct cache_def {scalar_t__ flags; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void reset_lstat_cache(struct cache_def *cache)
{
	strbuf_reset(&cache->path);
	cache->flags = 0;
	/*
	 * The track_flags and prefix_len_stat_func members is only
	 * set by the safeguard rule inside lstat_cache()
	 */
}