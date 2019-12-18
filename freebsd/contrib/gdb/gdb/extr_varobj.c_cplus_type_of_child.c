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
struct varobj {struct varobj* parent; } ;
struct type {int dummy; } ;

/* Variables and functions */
 scalar_t__ CPLUS_FAKE_CHILD (struct varobj*) ; 
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_STRUCT 129 
#define  TYPE_CODE_UNION 128 
 struct type* TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_N_BASECLASSES (struct type*) ; 
 struct type* c_type_of_child (struct varobj*,int) ; 
 char* cplus_name_of_child (struct varobj*,int) ; 
 struct type* get_type_deref (struct varobj*) ; 
 struct type* lookup_struct_elt_type (struct type*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static struct type *
cplus_type_of_child (struct varobj *parent, int index)
{
  struct type *type, *t;

  if (CPLUS_FAKE_CHILD (parent))
    {
      /* Looking for the type of a child of public, private, or protected. */
      t = get_type_deref (parent->parent);
    }
  else
    t = get_type_deref (parent);

  type = NULL;
  switch (TYPE_CODE (t))
    {
    case TYPE_CODE_STRUCT:
    case TYPE_CODE_UNION:
      if (CPLUS_FAKE_CHILD (parent))
	{
	  char *name = cplus_name_of_child (parent, index);
	  type = lookup_struct_elt_type (t, name, 0);
	  xfree (name);
	}
      else if (index < TYPE_N_BASECLASSES (t))
	type = TYPE_FIELD_TYPE (t, index);
      else
	{
	  /* special */
	  return NULL;
	}
      break;

    default:
      break;
    }

  if (type == NULL)
    return c_type_of_child (parent, index);

  return type;
}