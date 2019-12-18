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
struct TYPE_3__ {scalar_t__ y; } ;
typedef  TYPE_1__ trp_node ;

/* Variables and functions */
 TYPE_1__** heap ; 

void heap_fix_up (int j) {
  trp_node *tmp;
  int k = 0;

  while (j > 1 && heap[j]->y > heap[k = j / 2]->y) {
    tmp = heap[j], heap[j] = heap[k], heap[k] = tmp;
    j = k;
  }
}