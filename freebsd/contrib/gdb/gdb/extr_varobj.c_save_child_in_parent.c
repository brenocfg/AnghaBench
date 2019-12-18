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
struct varobj_child {struct varobj* child; struct varobj_child* next; } ;
struct varobj {struct varobj_child* children; } ;

/* Variables and functions */
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
save_child_in_parent (struct varobj *parent, struct varobj *child)
{
  struct varobj_child *vc;

  /* Insert the child at the top */
  vc = parent->children;
  parent->children =
    (struct varobj_child *) xmalloc (sizeof (struct varobj_child));

  parent->children->next = vc;
  parent->children->child = child;
}