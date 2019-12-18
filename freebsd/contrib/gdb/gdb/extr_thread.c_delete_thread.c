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
struct thread_info {struct thread_info* next; int /*<<< orphan*/  ptid; } ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_thread (struct thread_info*) ; 
 scalar_t__ ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct thread_info* thread_list ; 

void
delete_thread (ptid_t ptid)
{
  struct thread_info *tp, *tpprev;

  tpprev = NULL;

  for (tp = thread_list; tp; tpprev = tp, tp = tp->next)
    if (ptid_equal (tp->ptid, ptid))
      break;

  if (!tp)
    return;

  if (tpprev)
    tpprev->next = tp->next;
  else
    thread_list = tp->next;

  free_thread (tp);
}