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
struct lev_cache_change_disk_status {int /*<<< orphan*/  packed_location; } ;
struct cache_uri {int /*<<< orphan*/ * local_copy; struct cache_uri* hnext; } ;

/* Variables and functions */
 int CACHE_FEATURE_FAST_BOTTOM_ACCESS ; 
 int CACHE_FEATURE_LONG_QUERIES ; 
 int CACHE_URI_BUCKETS ; 
 struct cache_uri** H ; 
 long long INT_MAX ; 
 struct cache_uri* PNEXT (struct cache_uri*) ; 
 int /*<<< orphan*/  cache_change_disk_status (struct lev_cache_change_disk_status*,int) ; 
 int /*<<< orphan*/  cache_disk_filter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cache_features_mask ; 
 int cache_uri_delete_remote_disk (struct cache_uri*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disk_filter ; 
 int get_bucket_by_packed_location (int /*<<< orphan*/ ) ; 
 struct cache_uri* list_cached ; 
 int uri_hash_prime ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

__attribute__((used)) static int cache_delete_remote_disk (struct lev_cache_change_disk_status *E) {
  vkprintf (2, "cache_delete_remote_disk: starting\n");
  cache_change_disk_status (E, 1);
  cache_disk_filter_init (&disk_filter, E->packed_location);
  long long r = 0;
  int i;
  struct cache_uri *U, *B, *W;
  const int bucket = get_bucket_by_packed_location (E->packed_location);
  if (cache_features_mask & CACHE_FEATURE_LONG_QUERIES) {
    for (i = CACHE_URI_BUCKETS - 1; i >= 0; i--) {
      if (cache_features_mask & CACHE_FEATURE_FAST_BOTTOM_ACCESS) {
        if (i != 0 && i != bucket) {
          continue;
        }
      }
      B = &list_cached[i];
      for (U = PNEXT(B); U != B; U = W) {
        W = PNEXT(U);
        /* cache_uri_delete_remote_disk changes U->pnext field,
           since it calls cache_uri_update_local_copy
           which calls cache_uri_bucket_insert,
           in the case when URI flips cached state
        */
        int o = cache_uri_delete_remote_disk (U, &disk_filter);
        if (o > 0) {
          r += o;
        }
      }
    }
  } else {
    for (i = 0; i < uri_hash_prime; i++) {
      for (U = H[i]; U != NULL; U = U->hnext) {
        if (U->local_copy != NULL) {
          int o = cache_uri_delete_remote_disk (U, &disk_filter);
          if (o > 0) {
            r += o;
          }
        }
      }
    }
  }
  vkprintf (2, "cache_delete_remote_disk: r = %lld\n", r);
  return (r < INT_MAX) ? r : INT_MAX;
}