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
struct current_thread_cleanup {int /*<<< orphan*/  inferior_ptid; } ;

/* Variables and functions */
 int /*<<< orphan*/  restore_current_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (struct current_thread_cleanup*) ; 

__attribute__((used)) static void
do_restore_current_thread_cleanup (void *arg)
{
  struct current_thread_cleanup *old = arg;
  restore_current_thread (old->inferior_ptid);
  xfree (old);
}