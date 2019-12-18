#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cache_uri {int /*<<< orphan*/  last_access; } ;
typedef  enum cache_sorted_order { ____Placeholder_cache_sorted_order } cache_sorted_order ;
typedef  int /*<<< orphan*/  cache_top_access_result_t ;
struct TYPE_4__ {struct cache_uri** H; } ;
typedef  TYPE_1__ cache_heap_t ;

/* Variables and functions */
 int cache_output_heap (int /*<<< orphan*/ *,TYPE_1__*,int,int,int) ; 
 int cache_top_fill_heap (TYPE_1__*,int,int,int,int,int,int) ; 
 int cgsl_order_top ; 
 int /*<<< orphan*/  log_last_ts ; 

int cache_get_sorted_list (cache_top_access_result_t *R, int T, enum cache_sorted_order order, int limit, int flags, int min_rate) {
  cache_heap_t Heap;
  int cnt = cache_top_fill_heap (&Heap, T, order, limit, (flags & 8) ? 1 : 0, (flags & 16) ? 1 : 0, min_rate);
  if (cnt < 0) {
    return cnt;
  }

#ifdef CACHE_DEFEND_TOP_ACCESS_URIES_FROM_GC
  /* prevent top-priority uncached URIes returned by request from garbage collection */
  if ((flags & 16) && order == cgsl_order_top) {
    int i;
    for (i = 1; i <= cnt; i++) {
      struct cache_uri *U = Heap.H[i];
      U->last_access = log_last_ts;
    }
  }
#endif

  return cache_output_heap (R, &Heap, cnt, flags & (1 + 2 + 4), min_rate);
}