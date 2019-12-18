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
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_current_frame () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  print_stack_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switch_to_thread (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
restore_current_thread (ptid_t ptid)
{
  if (!ptid_equal (ptid, inferior_ptid))
    {
      switch_to_thread (ptid);
      print_stack_frame (get_current_frame (), 0, -1);
    }
}