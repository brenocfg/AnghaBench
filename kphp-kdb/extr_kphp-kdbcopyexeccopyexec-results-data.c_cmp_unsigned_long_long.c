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

/* Variables and functions */

__attribute__((used)) static int cmp_unsigned_long_long (const void *a, const void *b) {
  const unsigned long long x = *((const unsigned long long *) a);
  const unsigned long long y = *((const unsigned long long *) b);
  return (x < y) ? -1 : (x > y) ? 1 : 0;
}