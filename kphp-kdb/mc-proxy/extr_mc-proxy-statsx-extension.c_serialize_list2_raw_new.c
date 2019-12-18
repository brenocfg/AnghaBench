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

__attribute__((used)) static int *serialize_list2_raw_new (int *ptr, int *list, int num) {
  int i;
  *(ptr++) = *list;
  for (i = 0; i < 2 * (*list); i++) {
    *(ptr++) = list[i + 1];
  }
  return ptr;
}