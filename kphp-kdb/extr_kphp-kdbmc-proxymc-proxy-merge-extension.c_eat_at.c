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

int eat_at (const char *key, int key_len) {
  if (!key_len) {
    return 0;
  }
  int p = 0; 
  if (key[p] == '-') {
    p++;
  }
  while (p < key_len && key[p] >= '0' && key[p] <= '9') {
    p++;
  }
  if (p == key_len || p == 0 || key[p] != '@') {
    return 0;
  } else {
    p++;
    return p;
  }
}