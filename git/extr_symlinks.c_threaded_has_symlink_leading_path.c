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
 int FL_SYMLINK ; 
 int /*<<< orphan*/  USE_ONLY_LSTAT ; 
 int lstat_cache (struct cache_def*,char const*,int,int,int /*<<< orphan*/ ) ; 

int threaded_has_symlink_leading_path(struct cache_def *cache, const char *name, int len)
{
	return lstat_cache(cache, name, len, FL_SYMLINK|FL_DIR, USE_ONLY_LSTAT) & FL_SYMLINK;
}