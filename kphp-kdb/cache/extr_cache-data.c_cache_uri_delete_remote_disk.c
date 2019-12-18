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
struct cache_uri {int dummy; } ;
typedef  int /*<<< orphan*/  cache_disk_filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_MAX_LOCAL_COPIES ; 
 int /*<<< orphan*/ * LC ; 
 int /*<<< orphan*/  cache_local_copy_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cache_local_copy_unpack (struct cache_uri*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  cache_uri_decr_monthly_stats (struct cache_uri*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_uri_decr_server_stats (struct cache_uri*,int /*<<< orphan*/ *) ; 
 scalar_t__ cache_uri_local_copy_disk_filter_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_uri_update_local_copy (struct cache_uri*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

int cache_uri_delete_remote_disk (struct cache_uri *U, cache_disk_filter_t *F) {
  vkprintf (4, "cache_uri_delete_remote_disk: (U:%p) starting\n", U);
  int i, n, old_len, r = 0;
  n = cache_local_copy_unpack (U, LC, CACHE_MAX_LOCAL_COPIES, 0, &old_len);
  if (n < 0) {
    return -1;
  }
  for (i = 0; i < n; ) {
    if (cache_uri_local_copy_disk_filter_match (LC + i, F)) {
      r++;

#ifdef CACHE_FEATURE_MONTHLY_COUNTER_PERF_STATS
      cache_uri_decr_monthly_stats (U, LC + i);
#endif
      cache_uri_decr_server_stats (U, LC + i);

      n--;
      if (i != n) {
        cache_local_copy_cpy (&LC[i], &LC[n]);
      }
    } else {
      i++;
    }
  }
  if (r) {
    cache_uri_update_local_copy (U, LC, n, old_len);
  }
  vkprintf (4, "cache_uri_delete_remote_disk: ending\n");
  return r;
}