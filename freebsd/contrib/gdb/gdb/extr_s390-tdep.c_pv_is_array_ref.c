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
struct prologue_value {scalar_t__ kind; int k; } ;
typedef  enum pv_boolean { ____Placeholder_pv_boolean } pv_boolean ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 scalar_t__ pv_constant ; 
 int pv_definite_no ; 
 int pv_definite_yes ; 
 int pv_maybe ; 
 int /*<<< orphan*/  pv_subtract (struct prologue_value*,struct prologue_value*,struct prologue_value*) ; 

__attribute__((used)) static enum pv_boolean
pv_is_array_ref (struct prologue_value *addr,
                 CORE_ADDR size,
                 struct prologue_value *array_addr,
                 CORE_ADDR array_len, 
                 CORE_ADDR elt_size,
                 int *i)
{
  struct prologue_value offset;

  /* Note that, since ->k is a CORE_ADDR, and CORE_ADDR is unsigned,
     if addr is *before* the start of the array, then this isn't going
     to be negative...  */
  pv_subtract (&offset, addr, array_addr);

  if (offset.kind == pv_constant)
    {
      /* This is a rather odd test.  We want to know if the SIZE bytes
         at ADDR don't overlap the array at all, so you'd expect it to
         be an || expression: "if we're completely before || we're
         completely after".  But with unsigned arithmetic, things are
         different: since it's a number circle, not a number line, the
         right values for offset.k are actually one contiguous range.  */
      if (offset.k <= -size
          && offset.k >= array_len * elt_size)
        return pv_definite_no;
      else if (offset.k % elt_size != 0
               || size != elt_size)
        return pv_maybe;
      else
        {
          *i = offset.k / elt_size;
          return pv_definite_yes;
        }
    }
  else
    return pv_maybe;
}