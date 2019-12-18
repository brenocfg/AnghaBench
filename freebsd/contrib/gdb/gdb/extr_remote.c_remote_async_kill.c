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
typedef  int /*<<< orphan*/  catch_errors_ftype ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ERROR ; 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ kill_kludge ; 
 scalar_t__ putpkt ; 
 int /*<<< orphan*/  remote_desc ; 
 int /*<<< orphan*/  serial_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ target_is_async_p () ; 
 int /*<<< orphan*/  target_mourn_inferior () ; 

__attribute__((used)) static void
remote_async_kill (void)
{
  /* Unregister the file descriptor from the event loop. */
  if (target_is_async_p ())
    serial_async (remote_desc, NULL, 0);

  /* For some mysterious reason, wait_for_inferior calls kill instead of
     mourn after it gets TARGET_WAITKIND_SIGNALLED.  Work around it.  */
  if (kill_kludge)
    {
      kill_kludge = 0;
      target_mourn_inferior ();
      return;
    }

  /* Use catch_errors so the user can quit from gdb even when we aren't on
     speaking terms with the remote system.  */
  catch_errors ((catch_errors_ftype *) putpkt, "k", "", RETURN_MASK_ERROR);

  /* Don't wait for it to die.  I'm not really sure it matters whether
     we do or not.  For the existing stubs, kill is a noop.  */
  target_mourn_inferior ();
}