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
 scalar_t__ isdigit (char const) ; 

int get_at_prefix_length (const char *key, int key_len) {
  int i = 0;
  if (key_len > 0 && key[0] == '!') {
    i++;
  }
  if (i < key_len && key[i] == '-') {
    i++;
  }
  int j = i;
  while (j < key_len && isdigit (key[j])) {
    j++;
  }
  if (i == j) {
    return 0;
  }
  if (j < key_len && key[j] == '@') {
    return j + 1;
  }
  return 0;
}