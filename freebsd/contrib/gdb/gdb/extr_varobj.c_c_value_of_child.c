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
struct varobj {struct value* value; } ;
struct value {int dummy; } ;
struct type {int dummy; } ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 131 
#define  TYPE_CODE_PTR 130 
#define  TYPE_CODE_STRUCT 129 
#define  TYPE_CODE_UNION 128 
 int /*<<< orphan*/  builtin_type_int ; 
 int /*<<< orphan*/  gdb_value_ind (struct value*,struct value**) ; 
 int /*<<< orphan*/  gdb_value_struct_elt (int /*<<< orphan*/ *,struct value**,struct value**,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gdb_value_subscript (struct value*,struct value*,struct value**) ; 
 struct type* get_target_type (struct type*) ; 
 struct type* get_type (struct varobj*) ; 
 char* name_of_child (struct varobj*,int) ; 
 int /*<<< orphan*/  release_value (struct value*) ; 
 struct value* value_coerce_array (struct value*) ; 
 struct value* value_from_longest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct value* value_slice (struct value*,int,int) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static struct value *
c_value_of_child (struct varobj *parent, int index)
{
  struct value *value;
  struct value *temp;
  struct value *indval;
  struct type *type, *target;
  char *name;

  type = get_type (parent);
  target = get_target_type (type);
  name = name_of_child (parent, index);
  temp = parent->value;
  value = NULL;

  if (temp != NULL)
    {
      switch (TYPE_CODE (type))
	{
	case TYPE_CODE_ARRAY:
#if 0
	  /* This breaks if the array lives in a (vector) register. */
	  value = value_slice (temp, index, 1);
	  temp = value_coerce_array (value);
	  gdb_value_ind (temp, &value);
#else
	  indval = value_from_longest (builtin_type_int, (LONGEST) index);
	  gdb_value_subscript (temp, indval, &value);
#endif
	  break;

	case TYPE_CODE_STRUCT:
	case TYPE_CODE_UNION:
	  gdb_value_struct_elt (NULL, &value, &temp, NULL, name, NULL,
				"vstructure");
	  break;

	case TYPE_CODE_PTR:
	  switch (TYPE_CODE (target))
	    {
	    case TYPE_CODE_STRUCT:
	    case TYPE_CODE_UNION:
	      gdb_value_struct_elt (NULL, &value, &temp, NULL, name, NULL,
				    "vstructure");
	      break;

	    default:
	      gdb_value_ind (temp, &value);
	      break;
	    }
	  break;

	default:
	  break;
	}
    }

  if (value != NULL)
    release_value (value);

  xfree (name);
  return value;
}