#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cache_uri {int dummy; } ;
struct TYPE_3__ {struct cache_uri** H; } ;
typedef  TYPE_1__ cache_heap_t ;

/* Variables and functions */
 scalar_t__ cache_get_uri_heuristic (struct cache_uri*) ; 
 int /*<<< orphan*/  cache_get_uri_name (struct cache_uri*) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 

__attribute__((used)) static void cache_dump_priority_heap (const char *const heap_name, cache_heap_t *heap, int limit) {
  int j;
  kprintf ("%s:\n", heap_name);
  for (j = 1; j <= limit && j <= 10; j++) {
    struct cache_uri *U = heap->H[j];
    kprintf ("%d: %s %.6lg\n", j, cache_get_uri_name (U), (double) cache_get_uri_heuristic (U));
  }
}