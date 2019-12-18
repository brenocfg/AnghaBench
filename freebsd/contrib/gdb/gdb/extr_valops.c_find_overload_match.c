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
struct fn_field {int /*<<< orphan*/  type; } ;
struct cleanup {int dummy; } ;
typedef  struct symbol* badness_vector ;
typedef  enum oload_classification { ____Placeholder_oload_classification } oload_classification ;

/* Variables and functions */
#define  INCOMPATIBLE 129 
#define  NON_STANDARD 128 
 char* SYMBOL_CPLUS_DEMANGLED_NAME (struct symbol*) ; 
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_PTR ; 
 int /*<<< orphan*/ * TYPE_DOMAIN_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_FN_FIELD_VIRTUAL_P (struct fn_field*,int) ; 
 char* TYPE_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_TARGET_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int classify_oload_match (struct symbol**,int,int) ; 
 char* cp_func_name (char const*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*,char const*,...) ; 
 int find_oload_champ (struct type**,int,int,int,struct fn_field*,struct symbol**,struct symbol***) ; 
 int find_oload_champ_namespace (struct type**,int,char*,char const*,struct symbol***,struct symbol***) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int oload_method_static (int,struct fn_field*,int) ; 
 struct value* value_addr (struct value*) ; 
 struct fn_field* value_find_oload_method_list (struct value**,char*,int /*<<< orphan*/ ,int*,struct type**,int*) ; 
 struct value* value_fn_field (struct value**,struct fn_field*,int,struct type*,int) ; 
 struct value* value_virtual_fn_field (struct value**,struct fn_field*,int,struct type*,int) ; 
 int /*<<< orphan*/  warning (char*,char const*,...) ; 
 int /*<<< orphan*/  xfree ; 

int
find_overload_match (struct type **arg_types, int nargs, char *name, int method,
		     int lax, struct value **objp, struct symbol *fsym,
		     struct value **valp, struct symbol **symp, int *staticp)
{
  struct value *obj = (objp ? *objp : NULL);

  int oload_champ;		/* Index of best overloaded function */

  struct badness_vector *oload_champ_bv = NULL;		/* The measure for the current best match */

  struct value *temp = obj;
  struct fn_field *fns_ptr = NULL;	/* For methods, the list of overloaded methods */
  struct symbol **oload_syms = NULL;	/* For non-methods, the list of overloaded function symbols */
  int num_fns = 0;		/* Number of overloaded instances being considered */
  struct type *basetype = NULL;
  int boffset;
  int ix;
  int static_offset;
  struct cleanup *old_cleanups = NULL;

  const char *obj_type_name = NULL;
  char *func_name = NULL;
  enum oload_classification match_quality;

  /* Get the list of overloaded methods or functions */
  if (method)
    {
      obj_type_name = TYPE_NAME (VALUE_TYPE (obj));
      /* Hack: evaluate_subexp_standard often passes in a pointer
         value rather than the object itself, so try again */
      if ((!obj_type_name || !*obj_type_name) &&
	  (TYPE_CODE (VALUE_TYPE (obj)) == TYPE_CODE_PTR))
	obj_type_name = TYPE_NAME (TYPE_TARGET_TYPE (VALUE_TYPE (obj)));

      fns_ptr = value_find_oload_method_list (&temp, name, 0,
					      &num_fns,
					      &basetype, &boffset);
      if (!fns_ptr || !num_fns)
	error ("Couldn't find method %s%s%s",
	       obj_type_name,
	       (obj_type_name && *obj_type_name) ? "::" : "",
	       name);
      /* If we are dealing with stub method types, they should have
	 been resolved by find_method_list via value_find_oload_method_list
	 above.  */
      gdb_assert (TYPE_DOMAIN_TYPE (fns_ptr[0].type) != NULL);
      oload_champ = find_oload_champ (arg_types, nargs, method, num_fns,
				      fns_ptr, oload_syms, &oload_champ_bv);
    }
  else
    {
      const char *qualified_name = SYMBOL_CPLUS_DEMANGLED_NAME (fsym);
      func_name	= cp_func_name (qualified_name);

      /* If the name is NULL this must be a C-style function.
         Just return the same symbol. */
      if (func_name == NULL)
        {
	  *symp = fsym;
          return 0;
        }

      old_cleanups = make_cleanup (xfree, func_name);
      make_cleanup (xfree, oload_syms);
      make_cleanup (xfree, oload_champ_bv);

      oload_champ = find_oload_champ_namespace (arg_types, nargs,
						func_name,
						qualified_name,
						&oload_syms,
						&oload_champ_bv);
    }

  /* Check how bad the best match is.  */

  match_quality
    = classify_oload_match (oload_champ_bv, nargs,
			    oload_method_static (method, fns_ptr,
						 oload_champ));

  if (match_quality == INCOMPATIBLE)
    {
      if (method)
	error ("Cannot resolve method %s%s%s to any overloaded instance",
	       obj_type_name,
	       (obj_type_name && *obj_type_name) ? "::" : "",
	       name);
      else
	error ("Cannot resolve function %s to any overloaded instance",
	       func_name);
    }
  else if (match_quality == NON_STANDARD)
    {
      if (method)
	warning ("Using non-standard conversion to match method %s%s%s to supplied arguments",
		 obj_type_name,
		 (obj_type_name && *obj_type_name) ? "::" : "",
		 name);
      else
	warning ("Using non-standard conversion to match function %s to supplied arguments",
		 func_name);
    }

  if (method)
    {
      if (staticp != NULL)
	*staticp = oload_method_static (method, fns_ptr, oload_champ);
      if (TYPE_FN_FIELD_VIRTUAL_P (fns_ptr, oload_champ))
	*valp = value_virtual_fn_field (&temp, fns_ptr, oload_champ, basetype, boffset);
      else
	*valp = value_fn_field (&temp, fns_ptr, oload_champ, basetype, boffset);
    }
  else
    {
      *symp = oload_syms[oload_champ];
    }

  if (objp)
    {
      if (TYPE_CODE (VALUE_TYPE (temp)) != TYPE_CODE_PTR
	  && TYPE_CODE (VALUE_TYPE (*objp)) == TYPE_CODE_PTR)
	{
	  temp = value_addr (temp);
	}
      *objp = temp;
    }
  if (old_cleanups != NULL)
    do_cleanups (old_cleanups);

  switch (match_quality)
    {
    case INCOMPATIBLE:
      return 100;
    case NON_STANDARD:
      return 10;
    default:				/* STANDARD */
      return 0;
    }
}