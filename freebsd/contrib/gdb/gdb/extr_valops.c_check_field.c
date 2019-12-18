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

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int /*<<< orphan*/  COERCE_ARRAY (struct value*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_MEMBER ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_CODE_REF ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_CODE_UNION ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 int check_field_in (struct type*,char const*) ; 
 int /*<<< orphan*/  error (char*) ; 

int
check_field (struct value *arg1, const char *name)
{
  struct type *t;

  COERCE_ARRAY (arg1);

  t = VALUE_TYPE (arg1);

  /* Follow pointers until we get to a non-pointer.  */

  for (;;)
    {
      CHECK_TYPEDEF (t);
      if (TYPE_CODE (t) != TYPE_CODE_PTR && TYPE_CODE (t) != TYPE_CODE_REF)
	break;
      t = TYPE_TARGET_TYPE (t);
    }

  if (TYPE_CODE (t) == TYPE_CODE_MEMBER)
    error ("not implemented: member type in check_field");

  if (TYPE_CODE (t) != TYPE_CODE_STRUCT
      && TYPE_CODE (t) != TYPE_CODE_UNION)
    error ("Internal error: `this' is not an aggregate");

  return check_field_in (t, name);
}