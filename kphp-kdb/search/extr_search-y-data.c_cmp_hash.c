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
typedef  scalar_t__ hash_t ;

/* Variables and functions */

__attribute__((used)) static int cmp_hash (const void *a, const void *b) {
  const hash_t *x = (const hash_t *) a,
               *y = (const hash_t *) b;
  return *x < *y ? -1 : *x > *y ? 1 : 0;
}