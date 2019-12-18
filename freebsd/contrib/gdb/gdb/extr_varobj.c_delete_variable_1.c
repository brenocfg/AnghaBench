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
struct varobj {int /*<<< orphan*/ * obj_name; int /*<<< orphan*/ * parent; struct varobj_child* children; } ;
struct cpstack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cppush (struct cpstack**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_variable (struct varobj*) ; 
 int /*<<< orphan*/  remove_child_from_parent (int /*<<< orphan*/ *,struct varobj*) ; 
 int /*<<< orphan*/  uninstall_variable (struct varobj*) ; 
 int /*<<< orphan*/  xfree (struct varobj_child*) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
delete_variable_1 (struct cpstack **resultp, int *delcountp,
		   struct varobj *var, int only_children_p,
		   int remove_from_parent_p)
{
  struct varobj_child *vc;
  struct varobj_child *next;

  /* Delete any children of this variable, too. */
  for (vc = var->children; vc != NULL; vc = next)
    {
      if (!remove_from_parent_p)
	vc->child->parent = NULL;
      delete_variable_1 (resultp, delcountp, vc->child, 0, only_children_p);
      next = vc->next;
      xfree (vc);
    }

  /* if we were called to delete only the children we are done here */
  if (only_children_p)
    return;

  /* Otherwise, add it to the list of deleted ones and proceed to do so */
  /* If the name is null, this is a temporary variable, that has not
     yet been installed, don't report it, it belongs to the caller... */
  if (var->obj_name != NULL)
    {
      cppush (resultp, xstrdup (var->obj_name));
      *delcountp = *delcountp + 1;
    }

  /* If this variable has a parent, remove it from its parent's list */
  /* OPTIMIZATION: if the parent of this variable is also being deleted, 
     (as indicated by remove_from_parent_p) we don't bother doing an
     expensive list search to find the element to remove when we are
     discarding the list afterwards */
  if ((remove_from_parent_p) && (var->parent != NULL))
    {
      remove_child_from_parent (var->parent, var);
    }

  if (var->obj_name != NULL)
    uninstall_variable (var);

  /* Free memory associated with this variable */
  free_variable (var);
}