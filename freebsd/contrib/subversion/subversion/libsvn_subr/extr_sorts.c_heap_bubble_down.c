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
typedef  int /*<<< orphan*/  svn_priority_queue__t ;

/* Variables and functions */
 scalar_t__ heap_is_less (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  heap_swap (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
heap_bubble_down(svn_priority_queue__t *queue,
                 int idx)
{
  while (idx > 0 && heap_is_less(queue, idx, (idx - 1) / 2))
    {
      heap_swap(queue, idx, (idx - 1) / 2);
      idx = (idx - 1) / 2;
    }
}