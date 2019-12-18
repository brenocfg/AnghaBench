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
struct thread_info {TYPE_1__* private; } ;
struct private_thread_info {int dummy; } ;
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_2__ {int stable; int thrid; int lwpid; int /*<<< orphan*/  mapp; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct thread_info* add_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ target_has_execution ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 
 TYPE_1__* xmalloc (int) ; 

__attribute__((used)) static void
add_thread_uw (int thrid, int lwpid, CORE_ADDR mapp, ptid_t ptid)
{
  struct thread_info *newthread;

  if ((newthread = add_thread (ptid)) == NULL)
    error ("failed to create new thread structure");

  newthread->private = xmalloc (sizeof (struct private_thread_info));
  newthread->private->stable = 1;
  newthread->private->thrid = thrid;
  newthread->private->lwpid = lwpid;
  newthread->private->mapp = mapp;

  if (target_has_execution)
    printf_unfiltered ("[New %s]\n", target_pid_to_str (ptid));
}