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
struct varobj_child {struct varobj_child* next; struct varobj* child; } ;
struct varobj {struct varobj_child* children; } ;

/* Variables and functions */

__attribute__((used)) static void
remove_child_from_parent (struct varobj *parent, struct varobj *child)
{
  struct varobj_child *vc, *prev;

  /* Find the child in the parent's list */
  prev = NULL;
  for (vc = parent->children; vc != NULL;)
    {
      if (vc->child == child)
	break;
      prev = vc;
      vc = vc->next;
    }

  if (prev == NULL)
    parent->children = vc->next;
  else
    prev->next = vc->next;

}