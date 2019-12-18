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
struct thread_info {int /*<<< orphan*/  ptid; struct thread_info* next; } ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 scalar_t__ ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct thread_info* thread_list ; 

struct thread_info *
find_thread_pid (ptid_t ptid)
{
  struct thread_info *tp;

  for (tp = thread_list; tp; tp = tp->next)
    if (ptid_equal (tp->ptid, ptid))
      return tp;

  return NULL;
}