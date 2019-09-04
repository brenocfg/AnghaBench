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
struct cache_uri {int /*<<< orphan*/ * data; } ;
struct amortization_counter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_MAX_LOCAL_COPIES ; 
 scalar_t__ LC ; 
 int /*<<< orphan*/  amortization_counter_update (int /*<<< orphan*/ ,struct amortization_counter*) ; 
 int /*<<< orphan*/  cache_heap_insert (int /*<<< orphan*/ ,struct cache_uri*) ; 
 int cache_local_copy_unpack (struct cache_uri*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cache_uri_local_copy_disk_filter_match (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disk_filter ; 
 size_t heap_acounter_off ; 
 int /*<<< orphan*/  heap_foreach ; 
 int /*<<< orphan*/  tbl_foreach ; 
 int uri_off ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cache_heap_insert_uri_from_given_disk (struct cache_uri *U) {
  vkprintf (4, "cache_heap_insert_uri_from_given_disk (%s)\n", U->data + uri_off);
  int i;
  const int n = cache_local_copy_unpack (U, LC, CACHE_MAX_LOCAL_COPIES, 0, NULL);
  if (n < 0) {
    return;
  }
  for (i = 0; i < n; i++) {
    if (cache_uri_local_copy_disk_filter_match (LC + i, &disk_filter)) {
      struct amortization_counter *C = ((struct amortization_counter *) &U->data[heap_acounter_off]);
      amortization_counter_update (tbl_foreach, C);
      cache_heap_insert (heap_foreach, U);
      return;
    }
  }
}