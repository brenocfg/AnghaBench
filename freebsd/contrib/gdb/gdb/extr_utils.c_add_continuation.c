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
struct continuation_arg {int dummy; } ;
struct continuation {void (* continuation_hook ) (struct continuation_arg*) ;struct continuation* next; struct continuation_arg* arg_list; } ;

/* Variables and functions */
 struct continuation* cmd_continuation ; 
 scalar_t__ xmalloc (int) ; 

void
add_continuation (void (*continuation_hook) (struct continuation_arg *),
		  struct continuation_arg *arg_list)
{
  struct continuation *continuation_ptr;

  continuation_ptr =
    (struct continuation *) xmalloc (sizeof (struct continuation));
  continuation_ptr->continuation_hook = continuation_hook;
  continuation_ptr->arg_list = arg_list;
  continuation_ptr->next = cmd_continuation;
  cmd_continuation = continuation_ptr;
}