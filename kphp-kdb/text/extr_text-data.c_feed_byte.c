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

__attribute__((used)) static inline int feed_byte (int c, int *state) {
  if (*state == 2) {
    return 0;
  }
  if (*state == 5) {
    if (c != 1 && c != 2) {
      *state = 2;
      return 1;
    }
    *state = 1;
    return 0;
  }
  if (c == 9) {
    *state = 5;
  }
  return 0;
}