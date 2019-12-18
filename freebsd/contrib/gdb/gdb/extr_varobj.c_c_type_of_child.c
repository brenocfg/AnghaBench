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
struct varobj {struct type* type; } ;
struct type {int dummy; } ;

/* Variables and functions */
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 131 
#define  TYPE_CODE_PTR 130 
#define  TYPE_CODE_STRUCT 129 
#define  TYPE_CODE_UNION 128 
 struct type* get_target_type (struct type*) ; 
 struct type* lookup_struct_elt_type (struct type*,char*,int /*<<< orphan*/ ) ; 
 char* name_of_child (struct varobj*,int) ; 
 int /*<<< orphan*/  warning (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static struct type *
c_type_of_child (struct varobj *parent, int index)
{
  struct type *type;
  char *name = name_of_child (parent, index);

  switch (TYPE_CODE (parent->type))
    {
    case TYPE_CODE_ARRAY:
      type = get_target_type (parent->type);
      break;

    case TYPE_CODE_STRUCT:
    case TYPE_CODE_UNION:
      type = lookup_struct_elt_type (parent->type, name, 0);
      break;

    case TYPE_CODE_PTR:
      switch (TYPE_CODE (get_target_type (parent->type)))
	{
	case TYPE_CODE_STRUCT:
	case TYPE_CODE_UNION:
	  type = lookup_struct_elt_type (parent->type, name, 0);
	  break;

	default:
	  type = get_target_type (parent->type);
	  break;
	}
      break;

    default:
      /* This should not happen as only the above types have children */
      warning ("Child of parent whose type does not allow children");
      /* FIXME: Can we still go on? */
      type = NULL;
      break;
    }

  xfree (name);
  return type;
}