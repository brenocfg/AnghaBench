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

/* Variables and functions */
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ current_thread ; 
 int /*<<< orphan*/  do_child_fetch_inferior_registers (int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ thread_rec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
child_fetch_inferior_registers (int r)
{
  current_thread = thread_rec (PIDGET (inferior_ptid), TRUE);
  /* Check if current_thread exists.  Windows sometimes uses a non-existent
     thread id in its events */
  if (current_thread)
    do_child_fetch_inferior_registers (r);
}