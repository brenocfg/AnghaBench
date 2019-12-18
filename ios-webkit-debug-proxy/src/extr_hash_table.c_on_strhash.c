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
typedef  int /*<<< orphan*/  ht_t ;

/* Variables and functions */

intptr_t on_strhash(ht_t ht, const void *key) {
  int hc = 0;
  char *s = (char *)key;
  if (s) {
    int ch;
    while ((ch = *s++)) {
      hc = ((hc << 5) + hc) ^ ch;
    }
  }
  return hc;
}