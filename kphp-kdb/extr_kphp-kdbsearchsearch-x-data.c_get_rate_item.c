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
struct item {int extra; int* rates; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int FLAG_DELETED ; 
 int get_bitno (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_rate_item (struct item *I, int p) {
  if (!I || (I->extra & FLAG_DELETED)) { return 0;}
  int i = get_bitno (I->mask, p);
  return i >= 0 ? I->rates[i] : 0;
}