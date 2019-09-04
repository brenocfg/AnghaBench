#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  expected_gain; } ;

/* Variables and functions */
 TYPE_1__* H ; 
 int HN ; 
 int /*<<< orphan*/  assert (int) ; 
 int heap_sift_down (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void heap_pop (void) {
  assert (HN > 0);
  if (--HN) {
    int i = heap_sift_down (1, H[HN+1].expected_gain);
    H[i] = H[HN+1];
  }
}