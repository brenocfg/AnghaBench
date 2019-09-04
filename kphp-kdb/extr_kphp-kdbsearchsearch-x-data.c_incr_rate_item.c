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
struct item {int mask; int* rates; int /*<<< orphan*/  rates_len; } ;

/* Variables and functions */
 size_t get_bitno (int,int) ; 
 int* zzrealloc_ushort_mask (int*,int,int,int) ; 

__attribute__((used)) static int incr_rate_item (struct item *I, int p, int rate_incr) {
  if ((I->mask & (1 << p)) == 0) {
    I->rates = zzrealloc_ushort_mask (I->rates, I->mask, I->mask | (1 << p), sizeof (int));
    I->mask |= (1 << p);
    I->rates_len++;
  }
  rate_incr += I->rates[get_bitno (I->mask, p)];
  I->rates[get_bitno (I->mask, p)] = rate_incr;
  return 1;
}