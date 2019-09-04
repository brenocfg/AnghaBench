#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int node_id; int server_id; int disk_id; } ;
union cache_packed_local_copy_location {int /*<<< orphan*/  i; TYPE_1__ p; } ;
struct cache_uri {int dummy; } ;
struct amortization_counter {int dummy; } ;
typedef  enum cache_sorted_order { ____Placeholder_cache_sorted_order } cache_sorted_order ;
struct TYPE_7__ {int max_size; int /*<<< orphan*/  compare; scalar_t__ size; } ;
typedef  TYPE_2__ cache_heap_t ;

/* Variables and functions */
 int CACHE_ERR_LIMIT ; 
 int CACHE_ERR_UNKNOWN_T ; 
 int CACHE_FEATURE_FAST_BOTTOM_ACCESS ; 
 int CACHE_MAX_HEAP_SIZE ; 
 struct cache_uri* PNEXT (struct cache_uri*) ; 
 scalar_t__ TAT ; 
 scalar_t__ acounter_off ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cache_all_uri_cached_foreach (int /*<<< orphan*/  (*) (struct cache_uri*),int) ; 
 int /*<<< orphan*/  cache_disk_filter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cache_features_mask ; 
 int /*<<< orphan*/  cache_heap_cmp_bottom ; 
 int /*<<< orphan*/  cache_heap_cmp_top ; 
 int /*<<< orphan*/  cache_heap_insert_uri_from_given_disk (struct cache_uri*) ; 
 int cache_heap_sort (TYPE_2__*) ; 
 int cache_is_valid_disk (int,int,int) ; 
 int cgsl_order_bottom ; 
 int cgsl_order_top ; 
 int /*<<< orphan*/  disk_filter ; 
 int get_acounter_id_by_t (int) ; 
 int get_bucket_by_packed_location (int /*<<< orphan*/ ) ; 
 int heap_acounter_id ; 
 scalar_t__ heap_acounter_off ; 
 TYPE_2__* heap_foreach ; 
 struct cache_uri* list_cached ; 
 scalar_t__ tbl_foreach ; 

__attribute__((used)) static int cache_bottom_fill_heap_from_given_disk (cache_heap_t *heap, int T, int limit, int node_id, int server_id, int disk_id, enum cache_sorted_order order) {
  assert (order == cgsl_order_top || order == cgsl_order_bottom);
  int r = cache_is_valid_disk (node_id, server_id, disk_id);
  if (r < 0) {
    return r;
  }

  if (limit <= 0) {
    return CACHE_ERR_LIMIT;
  }

  heap_foreach = heap;
  heap_acounter_id = get_acounter_id_by_t (T);

  if (heap_acounter_id < 0) {
    return CACHE_ERR_UNKNOWN_T;
  }
  heap_acounter_off = acounter_off + heap_acounter_id * sizeof (struct amortization_counter);

  heap->size = 0;
  heap->max_size = (limit < CACHE_MAX_HEAP_SIZE) ? limit : CACHE_MAX_HEAP_SIZE;
  heap->compare = order == cgsl_order_top ? cache_heap_cmp_top : cache_heap_cmp_bottom;
  tbl_foreach = TAT + heap_acounter_id;
  union cache_packed_local_copy_location u;
  u.p.node_id = node_id;
  u.p.server_id = server_id;
  u.p.disk_id = disk_id;
  cache_disk_filter_init (&disk_filter, u.i);
  if (cache_features_mask & CACHE_FEATURE_FAST_BOTTOM_ACCESS) {
    int i;
    const int bucket = get_bucket_by_packed_location (u.i);
    /* zero bucket contains URIes with multiple locations */
    for (i = bucket; i >= 0; i -= bucket) {
      struct cache_uri *B = &list_cached[i], *U;
      for (U = PNEXT(B); U != B; U = PNEXT(U)) {
        cache_heap_insert_uri_from_given_disk (U);
      }
    }
  } else {
    cache_all_uri_cached_foreach (cache_heap_insert_uri_from_given_disk, order);
  }
  return cache_heap_sort (heap);
}