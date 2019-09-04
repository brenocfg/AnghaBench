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
 int /*<<< orphan*/  amortization_counter_update (int /*<<< orphan*/ ,struct amortization_counter*) ; 
 int /*<<< orphan*/  cache_heap_insert (int /*<<< orphan*/ ,struct cache_uri*) ; 
 size_t heap_acounter_off ; 
 int /*<<< orphan*/  heap_foreach ; 
 int /*<<< orphan*/  tbl_foreach ; 

__attribute__((used)) static void cache_heap_insert_uri (struct cache_uri *U) {
  struct amortization_counter *C = ((struct amortization_counter *) &U->data[heap_acounter_off]);
  amortization_counter_update (tbl_foreach, C);
  cache_heap_insert (heap_foreach, U);
}