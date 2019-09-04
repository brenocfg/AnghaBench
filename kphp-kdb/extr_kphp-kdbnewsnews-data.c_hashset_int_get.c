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
struct hashset_int {unsigned int size; int* h; } ;

/* Variables and functions */

int hashset_int_get (struct hashset_int *H, int id) {
  int h1, h2;
  h1 = ((unsigned int) id) % H->size;
  h2 = 1 + ((unsigned int) id) % (H->size - 1);
  while (H->h[h1] != 0) {
    if (H->h[h1] == id) {
      return 1;
    }
    h1 += h2;
    if (h1 >= H->size) { h1 -= H->size; }
  }
  return 0;
}