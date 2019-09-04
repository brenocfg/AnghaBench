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
struct item {int extra; int mask; int* rates; int /*<<< orphan*/  rates_len; } ;

/* Variables and functions */
 int FLAG_DELETED ; 
 size_t popcount_short (int) ; 
 int* zzrealloc_ushort_mask (int*,int,int,int) ; 

__attribute__((used)) static int set_multiple_rates_item (struct item *I, int mask, int *rates) {
  if (!I || (I->extra & FLAG_DELETED)) { return 0; }
  int new_mask = I->mask | mask;
  if (new_mask != I->mask) {
    int u = new_mask ^ I->mask;
    while (u) {
      I->rates_len++;
      u &= u - 1;
    }
    I->rates = zzrealloc_ushort_mask (I->rates, I->mask, new_mask, sizeof (int));
    I->mask = new_mask;
  }
  int i = 0, u = mask;
  while (u) {
    int x;
    u ^= x = u & -u;
    I->rates[popcount_short (new_mask & (x-1))] = rates[i++];
  }
  return 1;
}