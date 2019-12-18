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
 int lrand48 () ; 

__attribute__((used)) static unsigned long long make_secret (void) {
  unsigned long long r = 0;
  int i = 0;
  while (1) {
    r |= (lrand48 () >> 15) & 0xffff;
    if (++i == 4) {
      break;
    }
    r <<= 16;
  }
  return r;
}