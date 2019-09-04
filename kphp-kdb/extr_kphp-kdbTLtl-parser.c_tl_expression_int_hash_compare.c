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
struct tl_expression {scalar_t__ magic; } ;

/* Variables and functions */

__attribute__((used)) static int tl_expression_int_hash_compare (const void *a, const void *b) {
  const struct tl_expression *x = a, *y = b;
  return (x->magic < y->magic) ? -1 : ((x->magic > y->magic) ? 1 : 0);
}