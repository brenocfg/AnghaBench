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
struct TYPE_2__ {void* sig; int /*<<< orphan*/  integer; } ;
struct target_waitstatus {TYPE_1__ value; int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 scalar_t__ CHILD_SPECIAL_WAITSTATUS (struct target_waitstatus*,int) ; 
 int /*<<< orphan*/  TARGET_WAITKIND_EXITED ; 
 int /*<<< orphan*/  TARGET_WAITKIND_SIGNALLED ; 
 int /*<<< orphan*/  TARGET_WAITKIND_STOPPED ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  WIFSTOPPED (int) ; 
 int /*<<< orphan*/  WSTOPSIG (int) ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 void* target_signal_from_host (int /*<<< orphan*/ ) ; 

void
store_waitstatus (struct target_waitstatus *ourstatus, int hoststatus)
{
#ifdef CHILD_SPECIAL_WAITSTATUS
  /* CHILD_SPECIAL_WAITSTATUS should return nonzero and set *OURSTATUS
     if it wants to deal with hoststatus.  */
  if (CHILD_SPECIAL_WAITSTATUS (ourstatus, hoststatus))
    return;
#endif

  if (WIFEXITED (hoststatus))
    {
      ourstatus->kind = TARGET_WAITKIND_EXITED;
      ourstatus->value.integer = WEXITSTATUS (hoststatus);
    }
  else if (!WIFSTOPPED (hoststatus))
    {
      ourstatus->kind = TARGET_WAITKIND_SIGNALLED;
      ourstatus->value.sig = target_signal_from_host (WTERMSIG (hoststatus));
    }
  else
    {
      ourstatus->kind = TARGET_WAITKIND_STOPPED;
      ourstatus->value.sig = target_signal_from_host (WSTOPSIG (hoststatus));
    }
}