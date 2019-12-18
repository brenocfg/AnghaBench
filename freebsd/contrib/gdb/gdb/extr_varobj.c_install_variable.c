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
struct vlist {struct varobj* var; struct vlist* next; } ;
struct varobj {char* obj_name; TYPE_1__* root; } ;
struct TYPE_2__ {struct TYPE_2__* next; struct varobj* rootvar; } ;

/* Variables and functions */
 unsigned int VAROBJ_TABLE_SIZE ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  rootcount ; 
 TYPE_1__* rootlist ; 
 scalar_t__ strcmp (char*,char*) ; 
 struct vlist** varobj_table ; 
 struct vlist* xmalloc (int) ; 

__attribute__((used)) static int
install_variable (struct varobj *var)
{
  struct vlist *cv;
  struct vlist *newvl;
  const char *chp;
  unsigned int index = 0;
  unsigned int i = 1;

  for (chp = var->obj_name; *chp; chp++)
    {
      index = (index + (i++ * (unsigned int) *chp)) % VAROBJ_TABLE_SIZE;
    }

  cv = *(varobj_table + index);
  while ((cv != NULL) && (strcmp (cv->var->obj_name, var->obj_name) != 0))
    cv = cv->next;

  if (cv != NULL)
    error ("Duplicate variable object name");

  /* Add varobj to hash table */
  newvl = xmalloc (sizeof (struct vlist));
  newvl->next = *(varobj_table + index);
  newvl->var = var;
  *(varobj_table + index) = newvl;

  /* If root, add varobj to root list */
  if (var->root->rootvar == var)
    {
      /* Add to list of root variables */
      if (rootlist == NULL)
	var->root->next = NULL;
      else
	var->root->next = rootlist;
      rootlist = var->root;
      rootcount++;
    }

  return 1;			/* OK */
}