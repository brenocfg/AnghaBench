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

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_FLT ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_CODE_UNION ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_LENGTH (struct type*) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 scalar_t__ is_integer_like (struct type*) ; 
 scalar_t__ is_pointer_like (struct type*) ; 

__attribute__((used)) static int
alignment_of (struct type *type)
{
  int alignment;

  if (is_integer_like (type)
      || is_pointer_like (type)
      || TYPE_CODE (type) == TYPE_CODE_FLT)
    alignment = TYPE_LENGTH (type);
  else if (TYPE_CODE (type) == TYPE_CODE_STRUCT
           || TYPE_CODE (type) == TYPE_CODE_UNION)
    {
      int i;

      alignment = 1;
      for (i = 0; i < TYPE_NFIELDS (type); i++)
        {
          int field_alignment = alignment_of (TYPE_FIELD_TYPE (type, i));

          if (field_alignment > alignment)
            alignment = field_alignment;
        }
    }
  else
    alignment = 1;

  /* Check that everything we ever return is a power of two.  Lots of
     code doesn't want to deal with aligning things to arbitrary
     boundaries.  */
  gdb_assert ((alignment & (alignment - 1)) == 0);

  return alignment;
}