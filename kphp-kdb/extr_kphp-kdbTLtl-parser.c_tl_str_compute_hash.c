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
struct tl_hashmap {unsigned int size; } ;

/* Variables and functions */

__attribute__((used)) static inline void tl_str_compute_hash (struct tl_hashmap *self, const char *s, int *h1, int *h2) {
  unsigned int p1 = 0, p2 = 0;
  while (*s) {
    p1 = 239 * p1 + (*s);
    p2 = 3 * p2 + (*s);
    s++;
  }
  *h1 = p1 % self->size;
  *h2 = 1 + (p2 % (self->size - 1));
}