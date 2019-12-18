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
struct continuation {struct continuation* next; } ;

/* Variables and functions */
 struct continuation* cmd_continuation ; 
 int /*<<< orphan*/  xfree (struct continuation*) ; 

void
discard_all_continuations (void)
{
  struct continuation *continuation_ptr;

  while (cmd_continuation)
    {
      continuation_ptr = cmd_continuation;
      cmd_continuation = continuation_ptr->next;
      xfree (continuation_ptr);
    }
}