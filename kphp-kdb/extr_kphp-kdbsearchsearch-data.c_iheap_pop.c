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
struct TYPE_3__ {scalar_t__ item_id; int /*<<< orphan*/  cur; } ;
typedef  TYPE_1__ iheap_en_t ;

/* Variables and functions */
 TYPE_1__** H ; 
 int HC ; 

__attribute__((used)) static void iheap_pop (void) {
  int i, j;
  iheap_en_t *A;

  if (!HC) { return; }
  A = H[1];
  if (!A->cur) {
    A = H[HC--];
    if (!HC) { return; }
  }

  i = 1;
  while (1) {
    j = i*2;
    if (j > HC) { break; }
    if (j < HC && H[j+1]->item_id < H[j]->item_id) { j++; }
    if (A->item_id <= H[j]->item_id) { break; }
    H[i] = H[j];
    i = j;
  }
  H[i] = A;
}