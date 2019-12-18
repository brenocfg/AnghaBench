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
 scalar_t__ BASETYPE_VIA_VIRTUAL (struct type*,int) ; 
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 struct type* TYPE_BASECLASS (struct type*,int) ; 
 int TYPE_BASECLASS_BITPOS (struct type*,int) ; 
 struct fn_field* TYPE_FN_FIELDLIST1 (struct type*,int) ; 
 int TYPE_FN_FIELDLIST_LENGTH (struct type*,int) ; 
 char* TYPE_FN_FIELDLIST_NAME (struct type*,int) ; 
 scalar_t__ TYPE_HAS_VTABLE (struct type*) ; 
 int TYPE_NFN_FIELDS (struct type*) ; 
 int TYPE_N_BASECLASSES (struct type*) ; 
 scalar_t__ VALUE_ADDRESS (struct value*) ; 
 scalar_t__ VALUE_CONTENTS (struct value*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS_ALL (struct value*) ; 
 scalar_t__ VALUE_EMBEDDED_OFFSET (struct value*) ; 
 int VALUE_OFFSET (struct value*) ; 
 int baseclass_offset (struct type*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  check_stub_method_group (struct type*,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  find_rt_vbase_offset (struct type*,struct type*,int /*<<< orphan*/ ,scalar_t__,int*,int*) ; 
 scalar_t__ strcmp_iw (char*,char*) ; 

__attribute__((used)) static struct fn_field *
find_method_list (struct value **argp, char *method, int offset,
		  struct type *type, int *num_fns,
		  struct type **basetype, int *boffset)
{
  int i;
  struct fn_field *f;
  CHECK_TYPEDEF (type);

  *num_fns = 0;

  /* First check in object itself */
  for (i = TYPE_NFN_FIELDS (type) - 1; i >= 0; i--)
    {
      /* pai: FIXME What about operators and type conversions? */
      char *fn_field_name = TYPE_FN_FIELDLIST_NAME (type, i);
      if (fn_field_name && (strcmp_iw (fn_field_name, method) == 0))
	{
	  int len = TYPE_FN_FIELDLIST_LENGTH (type, i);
	  struct fn_field *f = TYPE_FN_FIELDLIST1 (type, i);

	  *num_fns = len;
	  *basetype = type;
	  *boffset = offset;

	  /* Resolve any stub methods.  */
	  check_stub_method_group (type, i);

	  return f;
	}
    }

  /* Not found in object, check in base subobjects */
  for (i = TYPE_N_BASECLASSES (type) - 1; i >= 0; i--)
    {
      int base_offset;
      if (BASETYPE_VIA_VIRTUAL (type, i))
	{
	  if (TYPE_HAS_VTABLE (type))
	    {
	      /* HP aCC compiled type, search for virtual base offset
	       * according to HP/Taligent runtime spec.  */
	      int skip;
	      find_rt_vbase_offset (type, TYPE_BASECLASS (type, i),
				    VALUE_CONTENTS_ALL (*argp),
				    offset + VALUE_EMBEDDED_OFFSET (*argp),
				    &base_offset, &skip);
	      if (skip >= 0)
		error ("Virtual base class offset not found in vtable");
	    }
	  else
	    {
	      /* probably g++ runtime model */
	      base_offset = VALUE_OFFSET (*argp) + offset;
	      base_offset =
		baseclass_offset (type, i,
				  VALUE_CONTENTS (*argp) + base_offset,
				  VALUE_ADDRESS (*argp) + base_offset);
	      if (base_offset == -1)
		error ("virtual baseclass botch");
	    }
	}
      else
	/* non-virtual base, simply use bit position from debug info */
	{
	  base_offset = TYPE_BASECLASS_BITPOS (type, i) / 8;
	}
      f = find_method_list (argp, method, base_offset + offset,
			    TYPE_BASECLASS (type, i), num_fns, basetype,
			    boffset);
      if (f)
	return f;
    }
  return NULL;
}