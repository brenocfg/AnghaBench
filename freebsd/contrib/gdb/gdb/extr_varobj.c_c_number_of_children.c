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
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOUND_CANNOT_BE_DETERMINED ; 
 int /*<<< orphan*/  TYPE_ARRAY_UPPER_BOUND_TYPE (struct type*) ; 
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 133 
#define  TYPE_CODE_FUNC 132 
#define  TYPE_CODE_PTR 131 
#define  TYPE_CODE_STRUCT 130 
#define  TYPE_CODE_UNION 129 
#define  TYPE_CODE_VOID 128 
 int TYPE_LENGTH (struct type*) ; 
 int TYPE_NFIELDS (struct type*) ; 
 struct type* get_target_type (struct type*) ; 
 struct type* get_type (struct varobj*) ; 

__attribute__((used)) static int
c_number_of_children (struct varobj *var)
{
  struct type *type;
  struct type *target;
  int children;

  type = get_type (var);
  target = get_target_type (type);
  children = 0;

  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_ARRAY:
      if (TYPE_LENGTH (type) > 0 && TYPE_LENGTH (target) > 0
	  && TYPE_ARRAY_UPPER_BOUND_TYPE (type) != BOUND_CANNOT_BE_DETERMINED)
	children = TYPE_LENGTH (type) / TYPE_LENGTH (target);
      else
	children = -1;
      break;

    case TYPE_CODE_STRUCT:
    case TYPE_CODE_UNION:
      children = TYPE_NFIELDS (type);
      break;

    case TYPE_CODE_PTR:
      /* This is where things get compilcated. All pointers have one child.
         Except, of course, for struct and union ptr, which we automagically
         dereference for the user and function ptrs, which have no children.
         We also don't dereference void* as we don't know what to show.
         We can show char* so we allow it to be dereferenced.  If you decide
         to test for it, please mind that a little magic is necessary to
         properly identify it: char* has TYPE_CODE == TYPE_CODE_INT and 
         TYPE_NAME == "char" */

      switch (TYPE_CODE (target))
	{
	case TYPE_CODE_STRUCT:
	case TYPE_CODE_UNION:
	  children = TYPE_NFIELDS (target);
	  break;

	case TYPE_CODE_FUNC:
	case TYPE_CODE_VOID:
	  children = 0;
	  break;

	default:
	  children = 1;
	}
      break;

    default:
      /* Other types have no children */
      break;
    }

  return children;
}