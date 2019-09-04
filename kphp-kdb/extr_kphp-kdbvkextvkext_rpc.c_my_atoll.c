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
 int /*<<< orphan*/  assert (char const*) ; 

long long my_atoll (const char *s) {
  assert (s);
  int sign = 0;
  if (*s == '-') {
    s ++;
    sign = 1;
  }
  long long r = 0;
  while (*s && *s >= '0' && *s <= '9') {
    r = r * 10 + *(s ++) - '0';    
  }
  return sign ? -r : r;
}