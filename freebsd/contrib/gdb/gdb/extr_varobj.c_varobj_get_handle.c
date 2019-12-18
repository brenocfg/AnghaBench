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
struct vlist {struct varobj* var; struct vlist* next; } ;
struct varobj {int /*<<< orphan*/  obj_name; } ;

/* Variables and functions */
 unsigned int VAROBJ_TABLE_SIZE ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 struct vlist** varobj_table ; 

struct varobj *
varobj_get_handle (char *objname)
{
  struct vlist *cv;
  const char *chp;
  unsigned int index = 0;
  unsigned int i = 1;

  for (chp = objname; *chp; chp++)
    {
      index = (index + (i++ * (unsigned int) *chp)) % VAROBJ_TABLE_SIZE;
    }

  cv = *(varobj_table + index);
  while ((cv != NULL) && (strcmp (cv->var->obj_name, objname) != 0))
    cv = cv->next;

  if (cv == NULL)
    error ("Variable object not found");

  return cv->var;
}