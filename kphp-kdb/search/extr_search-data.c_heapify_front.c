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
struct item_with_rating {scalar_t__ V; int /*<<< orphan*/  I; } ;
struct TYPE_4__ {TYPE_1__* h; } ;
struct TYPE_3__ {int value; } ;

/* Variables and functions */
 int /*<<< orphan*/ * R ; 
 size_t* RS ; 
 scalar_t__* RV ; 
 int R_cnt ; 
 TYPE_2__ hm ; 

__attribute__((used)) static void heapify_front (struct item_with_rating *E, int i, int slot) {
  while (1) {
    int j = i << 1;
    if (j > R_cnt) { break; }
    if (j < R_cnt && RV[j] <  RV[j+1]) { j++; }
    if (E->V >= RV[j]) { break; }
    R[i] = R[j];
    RV[i] = RV[j];
    hm.h[RS[i] = RS[j]].value = i;
    i = j;
  }
  R[i] = E->I;
  RV[i] = E->V;
  hm.h[RS[i] = slot].value = i;
}