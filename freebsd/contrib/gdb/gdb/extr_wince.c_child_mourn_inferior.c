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
 int /*<<< orphan*/  CeRapiUninit () ; 
 int /*<<< orphan*/  DBG_CONTINUE ; 
 int /*<<< orphan*/  child_continue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  child_ops ; 
 scalar_t__ connection_initialized ; 
 int /*<<< orphan*/  generic_mourn_inferior () ; 
 int /*<<< orphan*/  stop_stub () ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
child_mourn_inferior (void)
{
  (void) child_continue (DBG_CONTINUE, -1);
  unpush_target (&child_ops);
  stop_stub ();
  CeRapiUninit ();
  connection_initialized = 0;
  generic_mourn_inferior ();
}