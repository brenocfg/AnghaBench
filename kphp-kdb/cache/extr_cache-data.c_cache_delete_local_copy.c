#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct cache_uri {int dummy; } ;
struct cache_local_copy {int flags; int /*<<< orphan*/  location; } ;
struct TYPE_8__ {int /*<<< orphan*/  location; } ;

/* Variables and functions */
 int CACHE_LOCAL_COPY_FLAG_INT ; 
 int CACHE_MAX_LOCAL_COPIES ; 
 TYPE_1__* LC ; 
 int /*<<< orphan*/  cache_local_copy_cpy (TYPE_1__*,TYPE_1__*) ; 
 int cache_local_copy_unpack (struct cache_uri*,TYPE_1__*,int,int,int*) ; 
 int /*<<< orphan*/  cache_local_copy_unpack_location (struct cache_uri*,struct cache_local_copy*) ; 
 int /*<<< orphan*/  cache_uri_decr_monthly_stats (struct cache_uri*,TYPE_1__*) ; 
 int /*<<< orphan*/  cache_uri_decr_server_stats (struct cache_uri*,TYPE_1__*) ; 
 int cache_uri_update_local_copy (struct cache_uri*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cache_delete_local_copy (struct cache_uri *U, struct cache_local_copy *L) {
  int i, n, old_len;
  n = cache_local_copy_unpack (U, LC, CACHE_MAX_LOCAL_COPIES, 1, &old_len);
  if (n < 0 || n >= CACHE_MAX_LOCAL_COPIES) {
    return -1;
  }
  if (L->flags & CACHE_LOCAL_COPY_FLAG_INT) {
    cache_local_copy_unpack_location (U, L);
  }
  for (i = 0; i < n; i++) {
    if (!strcmp (LC[i].location, L->location)) {
      break;
    }
  }
  if (i >= n) {
    return -1;
  }

#ifdef CACHE_FEATURE_MONTHLY_COUNTER_PERF_STATS
  cache_uri_decr_monthly_stats (U, LC + i);
#endif
  cache_uri_decr_server_stats (U, LC + i);

  n--;
  if (i != n) {
    cache_local_copy_cpy (&LC[i], &LC[n]);
  }
  return cache_uri_update_local_copy (U, LC, n, old_len);
}