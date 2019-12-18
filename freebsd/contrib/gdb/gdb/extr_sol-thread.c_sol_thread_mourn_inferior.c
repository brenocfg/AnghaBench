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
struct TYPE_2__ {int /*<<< orphan*/  (* to_mourn_inferior ) () ;} ;

/* Variables and functions */
 TYPE_1__ procfs_ops ; 
 int /*<<< orphan*/  sol_thread_ops ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sol_thread_mourn_inferior (void)
{
  unpush_target (&sol_thread_ops);
  procfs_ops.to_mourn_inferior ();
}