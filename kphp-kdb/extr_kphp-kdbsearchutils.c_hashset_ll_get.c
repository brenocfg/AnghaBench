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
struct hashset_ll {unsigned int size; long long* h; } ;

/* Variables and functions */

int hashset_ll_get (struct hashset_ll *H, long long id) {
  int h1, h2;
  long long D;
  h1 = ((unsigned int) id) % H->size;
  h2 = 1 + ((unsigned int) (id >> 32)) % (H->size - 1);
  while ((D = H->h[h1]) != 0) {
    if (D == id) {
      return 1;
    }
    h1 += h2;
    if (h1 >= H->size) { h1 -= H->size; }
  }
  return 0;
}