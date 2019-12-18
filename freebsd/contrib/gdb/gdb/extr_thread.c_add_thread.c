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
struct thread_info {struct thread_info* next; scalar_t__ num; int /*<<< orphan*/  ptid; } ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 scalar_t__ highest_thread_num ; 
 int /*<<< orphan*/  memset (struct thread_info*,int /*<<< orphan*/ ,int) ; 
 struct thread_info* thread_list ; 
 scalar_t__ xmalloc (int) ; 

struct thread_info *
add_thread (ptid_t ptid)
{
  struct thread_info *tp;

  tp = (struct thread_info *) xmalloc (sizeof (*tp));
  memset (tp, 0, sizeof (*tp));
  tp->ptid = ptid;
  tp->num = ++highest_thread_num;
  tp->next = thread_list;
  thread_list = tp;
  return tp;
}