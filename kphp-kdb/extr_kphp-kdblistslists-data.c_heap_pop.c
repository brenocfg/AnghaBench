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
struct TYPE_2__ {int /*<<< orphan*/  global_id; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 TYPE_1__* H ; 
 int HN ; 
 int /*<<< orphan*/  assert (int) ; 
 int heap_sift_down (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void heap_pop (void) {
  assert (HN > 0);
  if (--HN) {
    int i = heap_sift_down (H[HN+1].value, H[HN+1].global_id);
    H[i] = H[HN+1];
  }
}