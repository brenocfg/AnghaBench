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
struct varobj {int dummy; } ;
struct cpstack {int dummy; } ;

/* Variables and functions */
 char* cppop (struct cpstack**) ; 
 int /*<<< orphan*/  cppush (struct cpstack**,int /*<<< orphan*/ *) ; 
 int delete_variable (struct cpstack**,struct varobj*,int) ; 
 int /*<<< orphan*/  warning (char*,int) ; 
 char** xmalloc (int) ; 

int
varobj_delete (struct varobj *var, char ***dellist, int only_children)
{
  int delcount;
  int mycount;
  struct cpstack *result = NULL;
  char **cp;

  /* Initialize a stack for temporary results */
  cppush (&result, NULL);

  if (only_children)
    /* Delete only the variable children */
    delcount = delete_variable (&result, var, 1 /* only the children */ );
  else
    /* Delete the variable and all its children */
    delcount = delete_variable (&result, var, 0 /* parent+children */ );

  /* We may have been asked to return a list of what has been deleted */
  if (dellist != NULL)
    {
      *dellist = xmalloc ((delcount + 1) * sizeof (char *));

      cp = *dellist;
      mycount = delcount;
      *cp = cppop (&result);
      while ((*cp != NULL) && (mycount > 0))
	{
	  mycount--;
	  cp++;
	  *cp = cppop (&result);
	}

      if (mycount || (*cp != NULL))
	warning ("varobj_delete: assertion failed - mycount(=%d) <> 0",
		 mycount);
    }

  return delcount;
}