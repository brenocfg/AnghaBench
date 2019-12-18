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
struct cleanup {void* arg; int /*<<< orphan*/ * function; struct cleanup* next; } ;
typedef  int /*<<< orphan*/  make_cleanup_ftype ;

/* Variables and functions */
 scalar_t__ xmalloc (int) ; 

struct cleanup *
make_my_cleanup (struct cleanup **pmy_chain, make_cleanup_ftype *function,
		 void *arg)
{
  struct cleanup *new
    = (struct cleanup *) xmalloc (sizeof (struct cleanup));
  struct cleanup *old_chain = *pmy_chain;

  new->next = *pmy_chain;
  new->function = function;
  new->arg = arg;
  *pmy_chain = new;

  return old_chain;
}