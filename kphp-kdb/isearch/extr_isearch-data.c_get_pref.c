#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {long long x; int y; } ;
typedef  TYPE_1__ hmap_pair_ll_int ;

/* Variables and functions */
 scalar_t__ H_ADD ; 
 int /*<<< orphan*/  h_pref ; 
 TYPE_1__* hmap_ll_int_get (int /*<<< orphan*/ *,TYPE_1__) ; 

int get_pref (long long h) {
  h += H_ADD;
  hmap_pair_ll_int tmp, *ptmp;
  tmp.x = h;
  tmp.y = 0;
  ptmp = hmap_ll_int_get (&h_pref, tmp);
  if (ptmp == NULL) {
    return 0;
  }

  return ptmp->y;
}