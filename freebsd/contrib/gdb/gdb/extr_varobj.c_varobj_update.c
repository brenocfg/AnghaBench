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
struct vstack {int dummy; } ;
struct varobj_child {struct varobj* child; struct varobj_child* next; } ;
struct varobj {int error; struct value* value; scalar_t__ updated; int /*<<< orphan*/  index; int /*<<< orphan*/  parent; struct varobj_child* children; TYPE_1__* root; } ;
struct value {int dummy; } ;
struct frame_info {int dummy; } ;
struct frame_id {int dummy; } ;
struct TYPE_2__ {struct varobj* rootvar; } ;

/* Variables and functions */
 int /*<<< orphan*/  deprecated_selected_frame ; 
 struct frame_info* frame_find_by_id (struct frame_id) ; 
 struct frame_id get_frame_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_value_equal (struct value*,struct value*,int*) ; 
 int /*<<< orphan*/  select_frame (struct frame_info*) ; 
 scalar_t__ type_changeable (struct varobj*) ; 
 int /*<<< orphan*/  value_free (struct value*) ; 
 struct value* value_of_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct value* value_of_root (struct varobj**,int*) ; 
 struct varobj* vpop (struct vstack**) ; 
 int /*<<< orphan*/  vpush (struct vstack**,struct varobj*) ; 
 int /*<<< orphan*/  warning (char*) ; 
 struct varobj** xmalloc (int) ; 

int
varobj_update (struct varobj **varp, struct varobj ***changelist)
{
  int changed = 0;
  int type_changed;
  int i;
  int vleft;
  int error2;
  struct varobj *v;
  struct varobj **cv;
  struct varobj **templist = NULL;
  struct value *new;
  struct vstack *stack = NULL;
  struct vstack *result = NULL;
  struct frame_id old_fid;
  struct frame_info *fi;

  /* sanity check: have we been passed a pointer? */
  if (changelist == NULL)
    return -1;

  /*  Only root variables can be updated... */
  if ((*varp)->root->rootvar != *varp)
    /* Not a root var */
    return -1;

  /* Save the selected stack frame, since we will need to change it
     in order to evaluate expressions. */
  old_fid = get_frame_id (deprecated_selected_frame);

  /* Update the root variable. value_of_root can return NULL
     if the variable is no longer around, i.e. we stepped out of
     the frame in which a local existed. We are letting the 
     value_of_root variable dispose of the varobj if the type
     has changed. */
  type_changed = 1;
  new = value_of_root (varp, &type_changed);
  if (new == NULL)
    {
      (*varp)->error = 1;
      return -1;
    }

  /* Initialize a stack for temporary results */
  vpush (&result, NULL);

  /* If this is a "use_selected_frame" varobj, and its type has changed,
     them note that it's changed. */
  if (type_changed)
    {
      vpush (&result, *varp);
      changed++;
    }
  /* If values are not equal, note that it's changed.
     There a couple of exceptions here, though.
     We don't want some types to be reported as "changed". */
  else if (type_changeable (*varp) &&
	   ((*varp)->updated || !my_value_equal ((*varp)->value, new, &error2)))
    {
      vpush (&result, *varp);
      (*varp)->updated = 0;
      changed++;
      /* error2 replaces var->error since this new value
         WILL replace the old one. */
      (*varp)->error = error2;
    }

  /* We must always keep around the new value for this root
     variable expression, or we lose the updated children! */
  value_free ((*varp)->value);
  (*varp)->value = new;

  /* Initialize a stack */
  vpush (&stack, NULL);

  /* Push the root's children */
  if ((*varp)->children != NULL)
    {
      struct varobj_child *c;
      for (c = (*varp)->children; c != NULL; c = c->next)
	vpush (&stack, c->child);
    }

  /* Walk through the children, reconstructing them all. */
  v = vpop (&stack);
  while (v != NULL)
    {
      /* Push any children */
      if (v->children != NULL)
	{
	  struct varobj_child *c;
	  for (c = v->children; c != NULL; c = c->next)
	    vpush (&stack, c->child);
	}

      /* Update this variable */
      new = value_of_child (v->parent, v->index);
      if (type_changeable (v) && 
          (v->updated || !my_value_equal (v->value, new, &error2)))
	{
	  /* Note that it's changed */
	  vpush (&result, v);
	  v->updated = 0;
	  changed++;
	}
      /* error2 replaces v->error since this new value
         WILL replace the old one. */
      v->error = error2;

      /* We must always keep new values, since children depend on it. */
      if (v->value != NULL)
	value_free (v->value);
      v->value = new;

      /* Get next child */
      v = vpop (&stack);
    }

  /* Alloc (changed + 1) list entries */
  /* FIXME: add a cleanup for the allocated list(s)
     because one day the select_frame called below can longjump */
  *changelist = xmalloc ((changed + 1) * sizeof (struct varobj *));
  if (changed > 1)
    {
      templist = xmalloc ((changed + 1) * sizeof (struct varobj *));
      cv = templist;
    }
  else
    cv = *changelist;

  /* Copy from result stack to list */
  vleft = changed;
  *cv = vpop (&result);
  while ((*cv != NULL) && (vleft > 0))
    {
      vleft--;
      cv++;
      *cv = vpop (&result);
    }
  if (vleft)
    warning ("varobj_update: assertion failed - vleft <> 0");

  if (changed > 1)
    {
      /* Now we revert the order. */
      for (i = 0; i < changed; i++)
	*(*changelist + i) = *(templist + changed - 1 - i);
      *(*changelist + changed) = NULL;
    }

  /* Restore selected frame */
  fi = frame_find_by_id (old_fid);
  if (fi)
    select_frame (fi);

  if (type_changed)
    return -2;
  else
    return changed;
}