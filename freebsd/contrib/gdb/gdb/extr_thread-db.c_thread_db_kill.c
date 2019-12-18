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
struct TYPE_2__ {int /*<<< orphan*/  (* to_kill ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  lwp_from_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_1__* target_beneath ; 

__attribute__((used)) static void
thread_db_kill (void)
{
  /* There's no need to save & restore inferior_ptid here, since the
     inferior isn't supposed to survive this function call.  */
  inferior_ptid = lwp_from_thread (inferior_ptid);
  target_beneath->to_kill ();
}