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
struct continuation {struct continuation* next; int /*<<< orphan*/  arg_list; int /*<<< orphan*/  (* continuation_hook ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct continuation* cmd_continuation ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (struct continuation*) ; 

void
do_all_continuations (void)
{
  struct continuation *continuation_ptr;
  struct continuation *saved_continuation;

  /* Copy the list header into another pointer, and set the global
     list header to null, so that the global list can change as a side
     effect of invoking the continuations and the processing of
     the preexisting continuations will not be affected. */
  continuation_ptr = cmd_continuation;
  cmd_continuation = NULL;

  /* Work now on the list we have set aside. */
  while (continuation_ptr)
    {
      (continuation_ptr->continuation_hook) (continuation_ptr->arg_list);
      saved_continuation = continuation_ptr;
      continuation_ptr = continuation_ptr->next;
      xfree (saved_continuation);
    }
}