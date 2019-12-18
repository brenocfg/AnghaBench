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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int HP_ACC_VBASE_START ; 
 struct type* TYPE_PRIMARY_BASE (struct type*) ; 
 int /*<<< orphan*/  builtin_type_int ; 
 int /*<<< orphan*/  error (char*) ; 
 int value_as_long (struct value*) ; 
 struct value* value_at (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int virtual_base_index_skip_primaries (struct type*,struct type*) ; 
 int virtual_base_list_length_skip_primaries (struct type*) ; 

void
find_rt_vbase_offset (struct type *type, struct type *basetype, char *valaddr,
		      int offset, int *boffset_p, int *skip_p)
{
  int boffset;			/* offset of virtual base */
  int index;			/* displacement to use in virtual table */
  int skip;

  struct value *vp;
  CORE_ADDR vtbl;		/* the virtual table pointer */
  struct type *pbc;		/* the primary base class */

  /* Look for the virtual base recursively in the primary base, first.
   * This is because the derived class object and its primary base
   * subobject share the primary virtual table.  */

  boffset = 0;
  pbc = TYPE_PRIMARY_BASE (type);
  if (pbc)
    {
      find_rt_vbase_offset (pbc, basetype, valaddr, offset, &boffset, &skip);
      if (skip < 0)
	{
	  *boffset_p = boffset;
	  *skip_p = -1;
	  return;
	}
    }
  else
    skip = 0;


  /* Find the index of the virtual base according to HP/Taligent
     runtime spec. (Depth-first, left-to-right.)  */
  index = virtual_base_index_skip_primaries (basetype, type);

  if (index < 0)
    {
      *skip_p = skip + virtual_base_list_length_skip_primaries (type);
      *boffset_p = 0;
      return;
    }

  /* pai: FIXME -- 32x64 possible problem */
  /* First word (4 bytes) in object layout is the vtable pointer */
  vtbl = *(CORE_ADDR *) (valaddr + offset);

  /* Before the constructor is invoked, things are usually zero'd out. */
  if (vtbl == 0)
    error ("Couldn't find virtual table -- object may not be constructed yet.");


  /* Find virtual base's offset -- jump over entries for primary base
   * ancestors, then use the index computed above.  But also adjust by
   * HP_ACC_VBASE_START for the vtable slots before the start of the
   * virtual base entries.  Offset is negative -- virtual base entries
   * appear _before_ the address point of the virtual table. */

  /* pai: FIXME -- 32x64 problem, if word = 8 bytes, change multiplier
     & use long type */

  /* epstein : FIXME -- added param for overlay section. May not be correct */
  vp = value_at (builtin_type_int, vtbl + 4 * (-skip - index - HP_ACC_VBASE_START), NULL);
  boffset = value_as_long (vp);
  *skip_p = -1;
  *boffset_p = boffset;
  return;
}