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
 int /*<<< orphan*/  CPLUS_FAKE_CHILD (struct varobj*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_CODE_UNION ; 
 scalar_t__ TYPE_N_BASECLASSES (struct type*) ; 
 int c_number_of_children (struct varobj*) ; 
 int /*<<< orphan*/  cplus_class_num_children (struct type*,int*) ; 
 struct type* get_type_deref (struct varobj*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 size_t v_private ; 
 size_t v_protected ; 
 size_t v_public ; 

__attribute__((used)) static int
cplus_number_of_children (struct varobj *var)
{
  struct type *type;
  int children, dont_know;

  dont_know = 1;
  children = 0;

  if (!CPLUS_FAKE_CHILD (var))
    {
      type = get_type_deref (var);

      if (((TYPE_CODE (type)) == TYPE_CODE_STRUCT) ||
	  ((TYPE_CODE (type)) == TYPE_CODE_UNION))
	{
	  int kids[3];

	  cplus_class_num_children (type, kids);
	  if (kids[v_public] != 0)
	    children++;
	  if (kids[v_private] != 0)
	    children++;
	  if (kids[v_protected] != 0)
	    children++;

	  /* Add any baseclasses */
	  children += TYPE_N_BASECLASSES (type);
	  dont_know = 0;

	  /* FIXME: save children in var */
	}
    }
  else
    {
      int kids[3];

      type = get_type_deref (var->parent);

      cplus_class_num_children (type, kids);
      if (strcmp (var->name, "public") == 0)
	children = kids[v_public];
      else if (strcmp (var->name, "private") == 0)
	children = kids[v_private];
      else
	children = kids[v_protected];
      dont_know = 0;
    }

  if (dont_know)
    children = c_number_of_children (var);

  return children;
}