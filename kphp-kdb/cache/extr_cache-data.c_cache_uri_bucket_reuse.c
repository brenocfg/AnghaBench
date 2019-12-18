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
struct cache_uri {int /*<<< orphan*/ * local_copy; } ;

/* Variables and functions */
 int CACHE_FEATURE_FAST_BOTTOM_ACCESS ; 
 int CACHE_FEATURE_LONG_QUERIES ; 
 int cache_features_mask ; 
 int /*<<< orphan*/  cache_uri_list_insert (scalar_t__,struct cache_uri*) ; 
 int /*<<< orphan*/  cache_uri_list_remove (struct cache_uri*) ; 
 scalar_t__ get_bucket (struct cache_uri*) ; 
 scalar_t__ list_cached ; 
 scalar_t__ list_uncached ; 

__attribute__((used)) static void cache_uri_bucket_reuse (struct cache_uri *U) {
  if (cache_features_mask & CACHE_FEATURE_LONG_QUERIES) {
    if (U->local_copy == NULL) {
      cache_uri_list_remove (U);
      cache_uri_list_insert (list_uncached + get_bucket (U), U);
    } else if (!(cache_features_mask & CACHE_FEATURE_FAST_BOTTOM_ACCESS)) {
      cache_uri_list_remove (U);
      cache_uri_list_insert (list_cached + get_bucket (U), U);
    }
  }
}