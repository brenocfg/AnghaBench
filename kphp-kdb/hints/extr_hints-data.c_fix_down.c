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
typedef  int /*<<< orphan*/  user ;

/* Variables and functions */
 scalar_t__ object_cmp (int /*<<< orphan*/ *,int,int,int) ; 

void fix_down (user *u, int *heap, int heap_size, int num) {
  int j, k, t;

  k = 1;
  while (1) {
    j = k;
    t = j * 2;
    if (t <= heap_size && object_cmp (u, heap[t], heap[k], num) < 0) {
      k = t;
    }
    t++;
    if (t <= heap_size && object_cmp (u, heap[t], heap[k], num) < 0) {
      k = t;
    }
    if (k != j) {
      t = heap[k], heap[k] = heap[j], heap[j] = t;
    } else {
      break;
    }
  }
}