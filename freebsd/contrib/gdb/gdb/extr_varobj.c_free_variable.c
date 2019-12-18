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
struct varobj {struct varobj* obj_name; struct varobj* name; struct varobj* root; int /*<<< orphan*/  exp; struct varobj* rootvar; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_current_contents (char**) ; 
 int /*<<< orphan*/  xfree (struct varobj*) ; 

__attribute__((used)) static void
free_variable (struct varobj *var)
{
  /* Free the expression if this is a root variable. */
  if (var->root->rootvar == var)
    {
      free_current_contents ((char **) &var->root->exp);
      xfree (var->root);
    }

  xfree (var->name);
  xfree (var->obj_name);
  xfree (var);
}