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
struct varobj {int /*<<< orphan*/  name; struct varobj_child* children; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct varobj *
child_exists (struct varobj *var, char *name)
{
  struct varobj_child *vc;

  for (vc = var->children; vc != NULL; vc = vc->next)
    {
      if (strcmp (vc->child->name, name) == 0)
	return vc->child;
    }

  return NULL;
}