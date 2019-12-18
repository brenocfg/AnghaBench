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
struct TYPE_2__ {scalar_t__ ti_valid; scalar_t__ th_valid; } ;

/* Variables and functions */

__attribute__((used)) static int
clear_lwpid_callback (struct thread_info *thread, void *dummy)
{
  /* If we know that our thread implementation is 1-to-1, we could save
     a certain amount of information; it's not clear how much, so we
     are always conservative.  */

  thread->private->th_valid = 0;
  thread->private->ti_valid = 0;

  return 0;
}