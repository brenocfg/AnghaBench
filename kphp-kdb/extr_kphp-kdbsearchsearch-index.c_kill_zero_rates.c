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
struct item {int mask; int rates_len; scalar_t__* rates; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

int kill_zero_rates (struct item *I) {
  int u = I->mask, m = 0, i = 0, mask = 0;
  while (u) {
    int x;
    u ^= x = u & -u;
    if (I->rates[i] || (x & 0xc000)) {
      mask |= x;
      I->rates[m++] = I->rates[i];
    }
    i++;
  }
  assert (i == I->rates_len);
  I->rates_len = m;
  I->mask = mask;
  return i;
}