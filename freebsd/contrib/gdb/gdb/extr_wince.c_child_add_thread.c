#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  h; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ thread_info ;
struct TYPE_7__ {TYPE_1__* next; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  add_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ thread_head ; 
 TYPE_1__* thread_rec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static thread_info *
child_add_thread (DWORD id, HANDLE h)
{
  thread_info *th;

  if ((th = thread_rec (id, FALSE)))
    return th;

  th = (thread_info *) xmalloc (sizeof (*th));
  memset (th, 0, sizeof (*th));
  th->id = id;
  th->h = h;
  th->next = thread_head.next;
  thread_head.next = th;
  add_thread (id);
  return th;
}