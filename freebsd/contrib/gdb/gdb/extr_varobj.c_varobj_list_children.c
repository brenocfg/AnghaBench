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
struct varobj {int num_children; } ;

/* Variables and functions */
 struct varobj* child_exists (struct varobj*,char*) ; 
 struct varobj* create_child (struct varobj*,int,char*) ; 
 char* name_of_child (struct varobj*,int) ; 
 int number_of_children (struct varobj*) ; 
 struct varobj** xmalloc (int) ; 

int
varobj_list_children (struct varobj *var, struct varobj ***childlist)
{
  struct varobj *child;
  char *name;
  int i;

  /* sanity check: have we been passed a pointer? */
  if (childlist == NULL)
    return -1;

  *childlist = NULL;

  if (var->num_children == -1)
    var->num_children = number_of_children (var);

  /* List of children */
  *childlist = xmalloc ((var->num_children + 1) * sizeof (struct varobj *));

  for (i = 0; i < var->num_children; i++)
    {
      /* Mark as the end in case we bail out */
      *((*childlist) + i) = NULL;

      /* check if child exists, if not create */
      name = name_of_child (var, i);
      child = child_exists (var, name);
      if (child == NULL)
	child = create_child (var, i, name);

      *((*childlist) + i) = child;
    }

  /* End of list is marked by a NULL pointer */
  *((*childlist) + i) = NULL;

  return var->num_children;
}