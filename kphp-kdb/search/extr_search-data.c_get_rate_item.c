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
struct TYPE_3__ {int extra; int mask; int* rates; } ;
typedef  TYPE_1__ item_t ;

/* Variables and functions */
 int FLAG_DELETED ; 
 size_t get_bitno (int,int) ; 

__attribute__((used)) static int get_rate_item (item_t *I, int p) {
  if (!I || (I->extra & FLAG_DELETED)) { return 0;}
  if (!(I->mask & (1 << p))) { return 0;}
  return I->rates[get_bitno (I->mask,p)];
}