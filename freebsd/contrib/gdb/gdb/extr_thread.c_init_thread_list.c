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
struct thread_info {struct thread_info* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_thread (struct thread_info*) ; 
 scalar_t__ highest_thread_num ; 
 struct thread_info* thread_list ; 

void
init_thread_list (void)
{
  struct thread_info *tp, *tpnext;

  highest_thread_num = 0;
  if (!thread_list)
    return;

  for (tp = thread_list; tp; tp = tpnext)
    {
      tpnext = tp->next;
      free_thread (tp);
    }

  thread_list = NULL;
}