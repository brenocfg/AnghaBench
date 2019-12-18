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

long long get_hash (const char *s, int sn) {
  long long h = 239;
  int i;       

  for (i = 0; i < sn; i++) {
    h = h * 999983 + s[i];
  }
  
  return h;
}