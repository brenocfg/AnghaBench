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
struct varobj {int /*<<< orphan*/  name; struct varobj* parent; } ;
struct type {int dummy; } ;

/* Variables and functions */
 scalar_t__ CPLUS_FAKE_CHILD (struct varobj*) ; 
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_STRUCT 129 
#define  TYPE_CODE_UNION 128 
 char* TYPE_FIELD_NAME (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FIELD_PRIVATE (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FIELD_PROTECTED (struct type*,int) ; 
 int TYPE_N_BASECLASSES (struct type*) ; 
 struct type* TYPE_VPTR_BASETYPE (struct type*) ; 
 int TYPE_VPTR_FIELDNO (struct type*) ; 
 char* c_name_of_child (struct varobj*,int) ; 
 int /*<<< orphan*/  cplus_class_num_children (struct type*,int*) ; 
 struct type* get_type_deref (struct varobj*) ; 
 char* savestring (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 size_t v_private ; 
 size_t v_public ; 

__attribute__((used)) static char *
cplus_name_of_child (struct varobj *parent, int index)
{
  char *name;
  struct type *type;

  if (CPLUS_FAKE_CHILD (parent))
    {
      /* Looking for children of public, private, or protected. */
      type = get_type_deref (parent->parent);
    }
  else
    type = get_type_deref (parent);

  name = NULL;
  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_STRUCT:
    case TYPE_CODE_UNION:
      if (CPLUS_FAKE_CHILD (parent))
	{
	  /* The fields of the class type are ordered as they
	     appear in the class.  We are given an index for a
	     particular access control type ("public","protected",
	     or "private").  We must skip over fields that don't
	     have the access control we are looking for to properly
	     find the indexed field. */
	  int type_index = TYPE_N_BASECLASSES (type);
	  if (strcmp (parent->name, "private") == 0)
	    {
	      while (index >= 0)
		{
	  	  if (TYPE_VPTR_BASETYPE (type) == type
	      	      && type_index == TYPE_VPTR_FIELDNO (type))
		    ; /* ignore vptr */
		  else if (TYPE_FIELD_PRIVATE (type, type_index))
		    --index;
		  ++type_index;
		}
	      --type_index;
	    }
	  else if (strcmp (parent->name, "protected") == 0)
	    {
	      while (index >= 0)
		{
	  	  if (TYPE_VPTR_BASETYPE (type) == type
	      	      && type_index == TYPE_VPTR_FIELDNO (type))
		    ; /* ignore vptr */
		  else if (TYPE_FIELD_PROTECTED (type, type_index))
		    --index;
		  ++type_index;
		}
	      --type_index;
	    }
	  else
	    {
	      while (index >= 0)
		{
	  	  if (TYPE_VPTR_BASETYPE (type) == type
	      	      && type_index == TYPE_VPTR_FIELDNO (type))
		    ; /* ignore vptr */
		  else if (!TYPE_FIELD_PRIVATE (type, type_index) &&
		      !TYPE_FIELD_PROTECTED (type, type_index))
		    --index;
		  ++type_index;
		}
	      --type_index;
	    }

	  name = TYPE_FIELD_NAME (type, type_index);
	}
      else if (index < TYPE_N_BASECLASSES (type))
	/* We are looking up the name of a base class */
	name = TYPE_FIELD_NAME (type, index);
      else
	{
	  int children[3];
	  cplus_class_num_children(type, children);

	  /* Everything beyond the baseclasses can
	     only be "public", "private", or "protected"

	     The special "fake" children are always output by varobj in
	     this order. So if INDEX == 2, it MUST be "protected". */
	  index -= TYPE_N_BASECLASSES (type);
	  switch (index)
	    {
	    case 0:
	      if (children[v_public] > 0)
	 	name = "public";
	      else if (children[v_private] > 0)
	 	name = "private";
	      else 
	 	name = "protected";
	      break;
	    case 1:
	      if (children[v_public] > 0)
		{
		  if (children[v_private] > 0)
		    name = "private";
		  else
		    name = "protected";
		}
	      else if (children[v_private] > 0)
	 	name = "protected";
	      break;
	    case 2:
	      /* Must be protected */
	      name = "protected";
	      break;
	    default:
	      /* error! */
	      break;
	    }
	}
      break;

    default:
      break;
    }

  if (name == NULL)
    return c_name_of_child (parent, index);
  else
    {
      if (name != NULL)
	name = savestring (name, strlen (name));
    }

  return name;
}