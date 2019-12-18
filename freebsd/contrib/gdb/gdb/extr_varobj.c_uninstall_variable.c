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
struct vlist {struct vlist* next; TYPE_1__* var; } ;
struct varobj_root {struct varobj_root* next; struct varobj* rootvar; } ;
struct varobj {char* obj_name; struct varobj_root* root; } ;
struct TYPE_2__ {int /*<<< orphan*/  obj_name; } ;

/* Variables and functions */
 unsigned int VAROBJ_TABLE_SIZE ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  rootcount ; 
 struct varobj_root* rootlist ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 struct vlist** varobj_table ; 
 scalar_t__ varobjdebug ; 
 int /*<<< orphan*/  warning (char*,char*) ; 
 int /*<<< orphan*/  xfree (struct vlist*) ; 

__attribute__((used)) static void
uninstall_variable (struct varobj *var)
{
  struct vlist *cv;
  struct vlist *prev;
  struct varobj_root *cr;
  struct varobj_root *prer;
  const char *chp;
  unsigned int index = 0;
  unsigned int i = 1;

  /* Remove varobj from hash table */
  for (chp = var->obj_name; *chp; chp++)
    {
      index = (index + (i++ * (unsigned int) *chp)) % VAROBJ_TABLE_SIZE;
    }

  cv = *(varobj_table + index);
  prev = NULL;
  while ((cv != NULL) && (strcmp (cv->var->obj_name, var->obj_name) != 0))
    {
      prev = cv;
      cv = cv->next;
    }

  if (varobjdebug)
    fprintf_unfiltered (gdb_stdlog, "Deleting %s\n", var->obj_name);

  if (cv == NULL)
    {
      warning
	("Assertion failed: Could not find variable object \"%s\" to delete",
	 var->obj_name);
      return;
    }

  if (prev == NULL)
    *(varobj_table + index) = cv->next;
  else
    prev->next = cv->next;

  xfree (cv);

  /* If root, remove varobj from root list */
  if (var->root->rootvar == var)
    {
      /* Remove from list of root variables */
      if (rootlist == var->root)
	rootlist = var->root->next;
      else
	{
	  prer = NULL;
	  cr = rootlist;
	  while ((cr != NULL) && (cr->rootvar != var))
	    {
	      prer = cr;
	      cr = cr->next;
	    }
	  if (cr == NULL)
	    {
	      warning
		("Assertion failed: Could not find varobj \"%s\" in root list",
		 var->obj_name);
	      return;
	    }
	  if (prer == NULL)
	    rootlist = NULL;
	  else
	    prer->next = cr->next;
	}
      rootcount--;
    }

}