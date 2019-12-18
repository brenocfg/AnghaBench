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
struct varobj {struct value* value; struct varobj* parent; } ;
struct value {int dummy; } ;
struct type {int dummy; } ;

/* Variables and functions */
 scalar_t__ CPLUS_FAKE_CHILD (struct varobj*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_CODE_REF ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_CODE_UNION ; 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_N_BASECLASSES (struct type*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 struct value* c_value_of_child (struct varobj*,int) ; 
 int /*<<< orphan*/  gdb_value_ind (struct value*,struct value**) ; 
 int /*<<< orphan*/  gdb_value_struct_elt (int /*<<< orphan*/ *,struct value**,struct value**,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*) ; 
 struct type* get_type_deref (struct varobj*) ; 
 char* name_of_child (struct varobj*,int) ; 
 int /*<<< orphan*/  release_value (struct value*) ; 
 struct value* value_cast (int /*<<< orphan*/ ,struct value*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static struct value *
cplus_value_of_child (struct varobj *parent, int index)
{
  struct type *type;
  struct value *value;

  if (CPLUS_FAKE_CHILD (parent))
    type = get_type_deref (parent->parent);
  else
    type = get_type_deref (parent);

  value = NULL;

  if (((TYPE_CODE (type)) == TYPE_CODE_STRUCT) ||
      ((TYPE_CODE (type)) == TYPE_CODE_UNION))
    {
      if (CPLUS_FAKE_CHILD (parent))
	{
	  char *name;
	  struct value *temp = parent->parent->value;

	  if (temp == NULL)
	    return NULL;

	  name = name_of_child (parent, index);
	  gdb_value_struct_elt (NULL, &value, &temp, NULL, name, NULL,
				"cplus_structure");
	  if (value != NULL)
	    release_value (value);

	  xfree (name);
	}
      else if (index >= TYPE_N_BASECLASSES (type))
	{
	  /* public, private, or protected */
	  return NULL;
	}
      else
	{
	  /* Baseclass */
	  if (parent->value != NULL)
	    {
	      struct value *temp = NULL;

	      if (TYPE_CODE (VALUE_TYPE (parent->value)) == TYPE_CODE_PTR
		  || TYPE_CODE (VALUE_TYPE (parent->value)) == TYPE_CODE_REF)
		{
		  if (!gdb_value_ind (parent->value, &temp))
		    return NULL;
		}
	      else
		temp = parent->value;

	      if (temp != NULL)
		{
		  value = value_cast (TYPE_FIELD_TYPE (type, index), temp);
		  release_value (value);
		}
	      else
		{
		  /* We failed to evaluate the parent's value, so don't even
		     bother trying to evaluate this child. */
		  return NULL;
		}
	    }
	}
    }

  if (value == NULL)
    return c_value_of_child (parent, index);

  return value;
}