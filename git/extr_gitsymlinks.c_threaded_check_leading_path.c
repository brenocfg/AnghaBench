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
 int FL_DIR ; 
 int FL_NOENT ; 
 int FL_SYMLINK ; 
 int /*<<< orphan*/  USE_ONLY_LSTAT ; 
 int lstat_cache_matchlen (struct cache_def*,char const*,int,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int threaded_check_leading_path(struct cache_def *cache, const char *name, int len)
{
	int flags;
	int match_len = lstat_cache_matchlen(cache, name, len, &flags,
			   FL_SYMLINK|FL_NOENT|FL_DIR, USE_ONLY_LSTAT);
	if (flags & FL_NOENT)
		return 0;
	else if (flags & FL_DIR)
		return -1;
	else
		return match_len;
}