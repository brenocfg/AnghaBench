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
struct cleanup {struct cleanup* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (struct cleanup*) ; 

void
discard_my_cleanups (struct cleanup **pmy_chain,
		     struct cleanup *old_chain)
{
  struct cleanup *ptr;
  while ((ptr = *pmy_chain) != old_chain)
    {
      *pmy_chain = ptr->next;
      xfree (ptr);
    }
}