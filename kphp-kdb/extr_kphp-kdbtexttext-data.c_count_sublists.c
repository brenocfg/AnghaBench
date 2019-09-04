#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ xor_mask; scalar_t__ and_mask; } ;
struct TYPE_3__ {scalar_t__ xor_mask; scalar_t__ and_mask; } ;

/* Variables and functions */
 int MAX_SUBLISTS ; 
 TYPE_2__* Sublists ; 
 TYPE_1__* Sublists_packed ; 
 int /*<<< orphan*/  assert (int) ; 
 int sublists_num ; 

int count_sublists (void) {
  int i = 0;
  while (Sublists[i].xor_mask || Sublists[i].and_mask) {
    Sublists_packed[i].and_mask = Sublists[i].and_mask;
    Sublists_packed[i].xor_mask = Sublists[i].xor_mask;
    i++;
  }
  sublists_num = i;
  assert (sublists_num <= MAX_SUBLISTS);
  return i;
}