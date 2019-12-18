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
struct TYPE_3__ {int /*<<< orphan*/ * tail; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 TYPE_1__ all_threads ; 
 int /*<<< orphan*/  for_each_inferior (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_one_thread ; 

void
clear_inferiors (void)
{
  for_each_inferior (&all_threads, free_one_thread);

  all_threads.head = all_threads.tail = NULL;
}