#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cache_uri {int /*<<< orphan*/ * data; } ;
struct amortization_counter {scalar_t__ value; } ;
struct TYPE_2__ {int size; struct cache_uri** H; } ;

/* Variables and functions */
 scalar_t__ GET_HEAP_VALUE (int) ; 
 int /*<<< orphan*/  amortization_counter_update (int /*<<< orphan*/ ,struct amortization_counter*) ; 
 size_t heap_acounter_off ; 
 TYPE_1__* heap_foreach ; 
 int /*<<< orphan*/  tbl_foreach ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void cache_top_heap_insert_uri_optimized2 (struct cache_uri *U) {
  struct amortization_counter *C = ((struct amortization_counter *) &U->data[heap_acounter_off]);
  if (unlikely(GET_HEAP_VALUE(1) < C->value)) {
    amortization_counter_update (tbl_foreach, C);
    if (GET_HEAP_VALUE(1) < C->value) {
      int i = 1;
      while (1) {
        int j = i << 1;
        if (j > heap_foreach->size) {
          break;
        }
        if (j < heap_foreach->size && GET_HEAP_VALUE(j) > GET_HEAP_VALUE(j+1)) {
          j++;
        }
        if (C->value <= GET_HEAP_VALUE(j)) {
          break;
        }
        heap_foreach->H[i] = heap_foreach->H[j];
        i = j;
      }
      heap_foreach->H[i] = U;
    }
  }
}