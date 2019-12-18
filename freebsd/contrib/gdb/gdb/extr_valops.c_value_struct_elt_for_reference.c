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
struct symbol {int dummy; } ;
struct fn_field {int dummy; } ;
typedef  enum noside { ____Placeholder_noside } noside ;
typedef  int /*<<< orphan*/  VALUE_TYPE ;
typedef  scalar_t__ LONGEST ;

/* Variables and functions */
 scalar_t__ BASETYPE_VIA_VIRTUAL (struct type*,int) ; 
 int /*<<< orphan*/  DMGL_ANSI ; 
 scalar_t__ METHOD_PTR_FROM_VOFFSET (int /*<<< orphan*/ ) ; 
 struct type* TYPE_BASECLASS (struct type*,int) ; 
 int TYPE_BASECLASS_BITPOS (struct type*,int) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_CODE_UNION ; 
 int TYPE_FIELD_BITPOS (struct type*,int) ; 
 char* TYPE_FIELD_NAME (struct type*,int) ; 
 scalar_t__ TYPE_FIELD_PACKED (struct type*,int) ; 
 scalar_t__ TYPE_FIELD_STATIC (struct type*,int) ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int) ; 
 struct fn_field* TYPE_FN_FIELDLIST1 (struct type*,int) ; 
 int TYPE_FN_FIELDLIST_LENGTH (struct type*,int) ; 
 char* TYPE_FN_FIELDLIST_NAME (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FN_FIELD_PHYSNAME (struct fn_field*,int) ; 
 struct type* TYPE_FN_FIELD_TYPE (struct fn_field*,int) ; 
 scalar_t__ TYPE_FN_FIELD_VIRTUAL_P (struct fn_field*,int) ; 
 int /*<<< orphan*/  TYPE_FN_FIELD_VOFFSET (struct fn_field*,int) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int TYPE_NFN_FIELDS (struct type*) ; 
 int TYPE_N_BASECLASSES (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 int /*<<< orphan*/  check_stub_method_group (struct type*,int) ; 
 scalar_t__ cplus_demangle_opname (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ destructor_name_p (char*,struct type*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  lookup_member_type (struct type*,struct type*) ; 
 int /*<<< orphan*/  lookup_reference_type (int /*<<< orphan*/ ) ; 
 struct symbol* lookup_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct value* read_var_value (struct symbol*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 struct value* value_from_longest (int /*<<< orphan*/ ,scalar_t__) ; 
 struct value* value_maybe_namespace_elt (struct type*,char*,int) ; 
 struct value* value_static_field (struct type*,int) ; 

__attribute__((used)) static struct value *
value_struct_elt_for_reference (struct type *domain, int offset,
				struct type *curtype, char *name,
				struct type *intype,
				enum noside noside)
{
  struct type *t = curtype;
  int i;
  struct value *v;

  if (TYPE_CODE (t) != TYPE_CODE_STRUCT
      && TYPE_CODE (t) != TYPE_CODE_UNION)
    error ("Internal error: non-aggregate type to value_struct_elt_for_reference");

  for (i = TYPE_NFIELDS (t) - 1; i >= TYPE_N_BASECLASSES (t); i--)
    {
      char *t_field_name = TYPE_FIELD_NAME (t, i);

      if (t_field_name && strcmp (t_field_name, name) == 0)
	{
	  if (TYPE_FIELD_STATIC (t, i))
	    {
	      v = value_static_field (t, i);
	      if (v == NULL)
		error ("static field %s has been optimized out",
		       name);
	      return v;
	    }
	  if (TYPE_FIELD_PACKED (t, i))
	    error ("pointers to bitfield members not allowed");

	  return value_from_longest
	    (lookup_reference_type (lookup_member_type (TYPE_FIELD_TYPE (t, i),
							domain)),
	     offset + (LONGEST) (TYPE_FIELD_BITPOS (t, i) >> 3));
	}
    }

  /* C++: If it was not found as a data field, then try to
     return it as a pointer to a method.  */

  /* Destructors are a special case.  */
  if (destructor_name_p (name, t))
    {
      error ("member pointers to destructors not implemented yet");
    }

  /* Perform all necessary dereferencing.  */
  while (intype && TYPE_CODE (intype) == TYPE_CODE_PTR)
    intype = TYPE_TARGET_TYPE (intype);

  for (i = TYPE_NFN_FIELDS (t) - 1; i >= 0; --i)
    {
      char *t_field_name = TYPE_FN_FIELDLIST_NAME (t, i);
      char dem_opname[64];

      if (strncmp (t_field_name, "__", 2) == 0 ||
	  strncmp (t_field_name, "op", 2) == 0 ||
	  strncmp (t_field_name, "type", 4) == 0)
	{
	  if (cplus_demangle_opname (t_field_name, dem_opname, DMGL_ANSI))
	    t_field_name = dem_opname;
	  else if (cplus_demangle_opname (t_field_name, dem_opname, 0))
	    t_field_name = dem_opname;
	}
      if (t_field_name && strcmp (t_field_name, name) == 0)
	{
	  int j = TYPE_FN_FIELDLIST_LENGTH (t, i);
	  struct fn_field *f = TYPE_FN_FIELDLIST1 (t, i);

	  check_stub_method_group (t, i);

	  if (intype == 0 && j > 1)
	    error ("non-unique member `%s' requires type instantiation", name);
	  if (intype)
	    {
	      while (j--)
		if (TYPE_FN_FIELD_TYPE (f, j) == intype)
		  break;
	      if (j < 0)
		error ("no member function matches that type instantiation");
	    }
	  else
	    j = 0;

	  if (TYPE_FN_FIELD_VIRTUAL_P (f, j))
	    {
	      return value_from_longest
		(lookup_reference_type
		 (lookup_member_type (TYPE_FN_FIELD_TYPE (f, j),
				      domain)),
		 (LONGEST) METHOD_PTR_FROM_VOFFSET (TYPE_FN_FIELD_VOFFSET (f, j)));
	    }
	  else
	    {
	      struct symbol *s = lookup_symbol (TYPE_FN_FIELD_PHYSNAME (f, j),
						0, VAR_DOMAIN, 0, NULL);
	      if (s == NULL)
		{
		  v = 0;
		}
	      else
		{
		  v = read_var_value (s, 0);
#if 0
		  VALUE_TYPE (v) = lookup_reference_type
		    (lookup_member_type (TYPE_FN_FIELD_TYPE (f, j),
					 domain));
#endif
		}
	      return v;
	    }
	}
    }
  for (i = TYPE_N_BASECLASSES (t) - 1; i >= 0; i--)
    {
      struct value *v;
      int base_offset;

      if (BASETYPE_VIA_VIRTUAL (t, i))
	base_offset = 0;
      else
	base_offset = TYPE_BASECLASS_BITPOS (t, i) / 8;
      v = value_struct_elt_for_reference (domain,
					  offset + base_offset,
					  TYPE_BASECLASS (t, i),
					  name,
					  intype,
					  noside);
      if (v)
	return v;
    }

  /* As a last chance, pretend that CURTYPE is a namespace, and look
     it up that way; this (frequently) works for types nested inside
     classes.  */

  return value_maybe_namespace_elt (curtype, name, noside);
}