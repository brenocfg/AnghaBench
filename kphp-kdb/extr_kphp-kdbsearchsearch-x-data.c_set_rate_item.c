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
 size_t get_bitno (int,int) ; 
 void* zzrealloc_ushort_mask (int*,int,int,int) ; 

__attribute__((used)) static int set_rate_item (struct item *I, int p, int rate) {
  if (!I || (I->extra & FLAG_DELETED)) { return 0; }

  if (!rate) {
    /* memory optimization: don't store zero rates into heap memory */
    if (I->mask & (1 << p)) {
      I->rates = zzrealloc_ushort_mask (I->rates, I->mask, I->mask ^ (1 << p), sizeof (int));
      I->mask ^= (1 << p);
      I->rates_len--;
    }
    return 1;
  }

  if ((I->mask & (1 << p)) == 0) {
    I->rates = zzrealloc_ushort_mask (I->rates, I->mask, I->mask | (1 << p), sizeof (int));
    I->mask |= (1 << p);
    I->rates_len++;
  }
  I->rates[get_bitno (I->mask, p)] = rate;
  return 1;
}