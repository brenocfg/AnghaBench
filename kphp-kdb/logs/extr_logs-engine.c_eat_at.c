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

__attribute__((used)) static inline void eat_at (const char *key, int key_len, char **new_key, int *new_len) {
  if (*key == '^') {
    key++;
    key_len--;
  }

  *new_key = (char *)key;
  *new_len = key_len;

  if ((*key >= '0' && *key <= '9') || (*key == '-' && key[1] >= '0' && key[1] <= '9')) {
    key++;
    while (*key >= '0' && *key <= '9') {
      key++;
    }

    if (*key++ == '@') {
      if (*key == '^') {
        key++;
      }

      *new_len -= (key - *new_key);
      *new_key = (char *)key;
    }
  }
}