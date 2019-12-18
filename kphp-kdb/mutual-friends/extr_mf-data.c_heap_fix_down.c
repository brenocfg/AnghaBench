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
 int heap_size ; 

void heap_fix_down (void) {
  int j, k, t;
  trp_node *tmp;
  k = 1;
  while (1) {
    j = k;
    t = j * 2;
    if (t <= heap_size && heap[t]->y > heap[k]->y) {
      k = t;
    }
    t++;
    if (t <= heap_size && heap[t]->y > heap[k]->y) {
      k = t;
    }
    if (k != j) {
      tmp = heap[k], heap[k] = heap[j], heap[j] = tmp;
    } else {
      break;
    }
  }
}