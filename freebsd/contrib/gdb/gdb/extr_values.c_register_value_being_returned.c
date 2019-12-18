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
struct regcache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int /*<<< orphan*/  EXTRACT_RETURN_VALUE (struct type*,struct regcache*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RETURN_VALUE_REGISTER_CONVENTION ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_VOID ; 
 int /*<<< orphan*/ * VALUE_CONTENTS_RAW (struct value*) ; 
 struct value* allocate_value (struct type*) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  gdbarch_return_value (int /*<<< orphan*/ ,struct type*,struct regcache*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdbarch_return_value_p (int /*<<< orphan*/ ) ; 

struct value *
register_value_being_returned (struct type *valtype, struct regcache *retbuf)
{
  struct value *val = allocate_value (valtype);

  /* If the function returns void, don't bother fetching the return
     value.  See also "using_struct_return".  */
  if (TYPE_CODE (valtype) == TYPE_CODE_VOID)
    return val;

  if (!gdbarch_return_value_p (current_gdbarch))
    {
      /* NOTE: cagney/2003-10-20: Unlike "gdbarch_return_value", the
         EXTRACT_RETURN_VALUE and USE_STRUCT_CONVENTION methods do not
         handle the edge case of a function returning a small
         structure / union in registers.  */
      CHECK_TYPEDEF (valtype);
      EXTRACT_RETURN_VALUE (valtype, retbuf, VALUE_CONTENTS_RAW (val));
      return val;
    }

  /* This function only handles "register convention".  */
  gdb_assert (gdbarch_return_value (current_gdbarch, valtype,
				    NULL, NULL, NULL)
	      == RETURN_VALUE_REGISTER_CONVENTION);
  gdbarch_return_value (current_gdbarch, valtype, retbuf,
			VALUE_CONTENTS_RAW (val) /*read*/, NULL /*write*/);
  return val;
}