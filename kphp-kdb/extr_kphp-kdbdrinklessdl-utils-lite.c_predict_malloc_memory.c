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

inline size_t predict_malloc_memory (size_t x) {
  if (x == (size_t)0) {
    return x;//this is very bad prediction, but right
  }
  size_t res = x + 3 * sizeof (long) - 1;
  res -= res % (2 * sizeof (long));
  if (res < 4 * sizeof (long)) {
    return 4 * sizeof (long);
  }
  return res;
}