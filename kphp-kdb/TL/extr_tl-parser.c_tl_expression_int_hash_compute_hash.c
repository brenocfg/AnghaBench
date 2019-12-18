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
struct tl_expression {scalar_t__ magic; } ;

/* Variables and functions */

__attribute__((used)) static void tl_expression_int_hash_compute_hash (struct tl_hashmap *self, void *p, int *h1, int *h2) {
  const struct tl_expression *E = p;
  *h1 = ((unsigned) E->magic) % self->size;
  *h2 = 1 + (((unsigned) E->magic) % (self->size - 1));
}