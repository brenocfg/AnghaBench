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
struct hashmap_ll_int {unsigned int size; TYPE_1__* h; } ;
struct TYPE_2__ {long long key; } ;

/* Variables and functions */

int hashmap_ll_int_get (struct hashmap_ll_int *H, long long id, int *p_slot_idx) {
  int h1, h2;
  long long D;
  h1 = ((unsigned int) id) % H->size;
  h2 = 1 + ((unsigned int) (id >> 32)) % (H->size - 1);
  while ((D = H->h[h1].key) != 0) {
    if (D == id) {
      *p_slot_idx = h1;
      return 1;
    }
    h1 += h2;
    if (h1 >= H->size) { h1 -= H->size; }
  }
  *p_slot_idx = h1;
  return 0;
}