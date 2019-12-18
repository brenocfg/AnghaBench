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

long long get_long (const char **s) {
  long long res = 0;
  while (**s <= '9' && **s >= '0') {
    res = res * 10 + **s - '0';
    (*s)++;
  }
  return res;
}