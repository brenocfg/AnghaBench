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
struct TYPE_2__ {int /*<<< orphan*/  breakpoint_len; int /*<<< orphan*/  breakpoint; } ;

/* Variables and functions */
 int /*<<< orphan*/  fbsd_init_signals () ; 
 int /*<<< orphan*/  fbsd_target_ops ; 
 int /*<<< orphan*/  init_registers () ; 
 int /*<<< orphan*/  set_breakpoint_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_target_ops (int /*<<< orphan*/ *) ; 
 TYPE_1__ the_low_target ; 
 scalar_t__ using_threads ; 

void
initialize_low (void)
{
  using_threads = 0;
  set_target_ops (&fbsd_target_ops);
  set_breakpoint_data (the_low_target.breakpoint,
		       the_low_target.breakpoint_len);
  init_registers ();
  fbsd_init_signals ();
}