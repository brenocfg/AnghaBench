#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct cache_uri {scalar_t__ local_copy; struct cache_uri* hnext; } ;
struct TYPE_7__ {int max_size; int /*<<< orphan*/  compare; scalar_t__ size; } ;
typedef  TYPE_1__ cache_heap_t ;

/* Variables and functions */
 int CACHE_MAX_HEAP_SIZE ; 
 struct cache_uri** H ; 
 int /*<<< orphan*/  cache_dump_priority_heap (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  cache_heap_insert (TYPE_1__*,struct cache_uri*) ; 
 int cache_heap_sort (TYPE_1__*) ; 
 int /*<<< orphan*/  cached_heap_cmp ; 
 int /*<<< orphan*/  uncached_heap_cmp ; 
 int uri_hash_prime ; 
 int verbosity ; 

int cache_get_priority_heaps (cache_heap_t *heap_cached, cache_heap_t *heap_uncached, int cached_limit, int uncached_limit, int *r1, int *r2) {
  int i;
  struct cache_uri *U;
  if (cached_limit == 0) {
    cached_limit = CACHE_MAX_HEAP_SIZE;
  }
  if (uncached_limit == 0) {
    uncached_limit = CACHE_MAX_HEAP_SIZE;
  }
  heap_cached->size = 0;
  heap_cached->max_size = (cached_limit < CACHE_MAX_HEAP_SIZE) ? cached_limit : CACHE_MAX_HEAP_SIZE;
  heap_cached->compare = cached_heap_cmp;
  heap_uncached->size = 0;
  heap_uncached->max_size = (uncached_limit < CACHE_MAX_HEAP_SIZE) ? uncached_limit : CACHE_MAX_HEAP_SIZE;
  heap_uncached->compare = uncached_heap_cmp;
  for (i = 0; i < uri_hash_prime; i++) {
    for (U = H[i]; U != NULL; U = U->hnext) {
      //cache_uri_compute_heuristic (U);
      cache_heap_insert (U->local_copy ? heap_cached : heap_uncached, U);
    }
  }
  *r1 = cache_heap_sort (heap_cached);
  if (verbosity >= 3) {
    cache_dump_priority_heap ("cached", heap_cached, *r1);
  }
  *r2 = cache_heap_sort (heap_uncached);
  if (verbosity >= 3) {
    cache_dump_priority_heap ("uncached", heap_uncached, *r2);
  }
  //TODO: protect useful files

  return 0;
}