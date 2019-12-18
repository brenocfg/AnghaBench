#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mask; int rates_len; scalar_t__* rates; } ;
typedef  TYPE_1__ item_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static long long get_hash_item (const item_t *I) {
  if ( (I->mask & 0xc000) == 0xc000) {
    assert (I->rates_len >= 2);
    /* since hash stored in 14 (lowest dword) and in 15 (highest word),
       we doesn't need to call get_bitno function
    */
    return (((unsigned long long) I->rates[I->rates_len-1]) << 32) | ((unsigned int) I->rates[I->rates_len-2]);
  }
  assert ( ! (I->mask & 0xc000) );
  return 0LL;
}