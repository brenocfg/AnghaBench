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
struct type {int dummy; } ;
typedef  enum type_code { ____Placeholder_type_code } type_code ;

/* Variables and functions */
 scalar_t__ RETURN_VALUE_ON_STACK (struct type*) ; 
 scalar_t__ RETURN_VALUE_STRUCT_CONVENTION ; 
 int TYPE_CODE (struct type*) ; 
 int TYPE_CODE_ARRAY ; 
 int TYPE_CODE_ERROR ; 
 int TYPE_CODE_STRUCT ; 
 int TYPE_CODE_UNION ; 
 int TYPE_CODE_VOID ; 
 int USE_STRUCT_CONVENTION (int,struct type*) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ gdbarch_return_value (int /*<<< orphan*/ ,struct type*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdbarch_return_value_p (int /*<<< orphan*/ ) ; 

int
using_struct_return (struct type *value_type, int gcc_p)
{
  enum type_code code = TYPE_CODE (value_type);

  if (code == TYPE_CODE_ERROR)
    error ("Function return type unknown.");

  if (code == TYPE_CODE_VOID)
    /* A void return value is never in memory.  See also corresponding
       code in "register_value_being_returned".  */
    return 0;

  if (!gdbarch_return_value_p (current_gdbarch))
    {
      /* FIXME: cagney/2003-10-01: The below is dead.  Instead an
	 architecture should implement "gdbarch_return_value".  Using
	 that new function it is possible to exactly specify the ABIs
	 "struct return" vs "register return" conventions.  */
      if (code == TYPE_CODE_STRUCT
	  || code == TYPE_CODE_UNION
	  || code == TYPE_CODE_ARRAY
	  || RETURN_VALUE_ON_STACK (value_type))
	return USE_STRUCT_CONVENTION (gcc_p, value_type);
      else
	return 0;
    }

  /* Probe the architecture for the return-value convention.  */
  return (gdbarch_return_value (current_gdbarch, value_type,
				NULL, NULL, NULL)
	  == RETURN_VALUE_STRUCT_CONVENTION);
}