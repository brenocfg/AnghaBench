#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct varobj {TYPE_2__* root; int /*<<< orphan*/  obj_name; int /*<<< orphan*/  name; } ;
struct value {int dummy; } ;
struct TYPE_4__ {TYPE_1__* lang; scalar_t__ use_selected_frame; struct varobj* rootvar; } ;
struct TYPE_3__ {struct value* (* value_of_root ) (struct varobj**) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  USE_SELECTED_FRAME ; 
 int /*<<< orphan*/  install_variable (struct varobj*) ; 
 int /*<<< orphan*/  savestring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 struct value* stub1 (struct varobj**) ; 
 struct varobj* varobj_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  varobj_delete (struct varobj*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  varobj_gen_name () ; 
 char* varobj_get_type (struct varobj*) ; 

__attribute__((used)) static struct value *
value_of_root (struct varobj **var_handle, int *type_changed)
{
  struct varobj *var;

  if (var_handle == NULL)
    return NULL;

  var = *var_handle;

  /* This should really be an exception, since this should
     only get called with a root variable. */

  if (var->root->rootvar != var)
    return NULL;

  if (var->root->use_selected_frame)
    {
      struct varobj *tmp_var;
      char *old_type, *new_type;
      old_type = varobj_get_type (var);
      tmp_var = varobj_create (NULL, var->name, (CORE_ADDR) 0,
			       USE_SELECTED_FRAME);
      if (tmp_var == NULL)
	{
	  return NULL;
	}
      new_type = varobj_get_type (tmp_var);
      if (strcmp (old_type, new_type) == 0)
	{
	  varobj_delete (tmp_var, NULL, 0);
	  *type_changed = 0;
	}
      else
	{
	  if (*type_changed)
	    {
	      tmp_var->obj_name =
		savestring (var->obj_name, strlen (var->obj_name));
	      varobj_delete (var, NULL, 0);
	    }
	  else
	    {
	      tmp_var->obj_name = varobj_gen_name ();
	    }
	  install_variable (tmp_var);
	  *var_handle = tmp_var;
	  var = *var_handle;
	  *type_changed = 1;
	}
    }
  else
    {
      *type_changed = 0;
    }

  return (*var->root->lang->value_of_root) (var_handle);
}