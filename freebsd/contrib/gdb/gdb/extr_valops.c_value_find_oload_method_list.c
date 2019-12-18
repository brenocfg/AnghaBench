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
struct value {int dummy; } ;
struct type {int dummy; } ;
struct fn_field {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COERCE_ARRAY (struct value*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_FUNC ; 
 scalar_t__ TYPE_CODE_MEMBER ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_CODE_REF ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_CODE_UNION ; 
 struct type* VALUE_TYPE (struct value*) ; 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct fn_field* find_method_list (struct value**,char*,int /*<<< orphan*/ ,struct type*,int*,struct type**,int*) ; 
 struct value* value_ind (struct value*) ; 

struct fn_field *
value_find_oload_method_list (struct value **argp, char *method, int offset,
			      int *num_fns, struct type **basetype,
			      int *boffset)
{
  struct type *t;

  t = check_typedef (VALUE_TYPE (*argp));

  /* code snarfed from value_struct_elt */
  while (TYPE_CODE (t) == TYPE_CODE_PTR || TYPE_CODE (t) == TYPE_CODE_REF)
    {
      *argp = value_ind (*argp);
      /* Don't coerce fn pointer to fn and then back again!  */
      if (TYPE_CODE (VALUE_TYPE (*argp)) != TYPE_CODE_FUNC)
	COERCE_ARRAY (*argp);
      t = check_typedef (VALUE_TYPE (*argp));
    }

  if (TYPE_CODE (t) == TYPE_CODE_MEMBER)
    error ("Not implemented: member type in value_find_oload_lis");

  if (TYPE_CODE (t) != TYPE_CODE_STRUCT
      && TYPE_CODE (t) != TYPE_CODE_UNION)
    error ("Attempt to extract a component of a value that is not a struct or union");

  return find_method_list (argp, method, 0, t, num_fns, basetype, boffset);
}