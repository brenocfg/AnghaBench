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
struct regcache {int dummy; } ;

/* Variables and functions */
 int SPARC64_D0_REGNUM ; 
 int SPARC64_Q0_REGNUM ; 
 int SPARC_F0_REGNUM ; 
 int TYPE_FIELD_BITPOS (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_LENGTH (struct type*) ; 
 int TYPE_NFIELDS (struct type*) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  regcache_cooked_read (struct regcache*,int,char*) ; 
 scalar_t__ sparc64_floating_p (struct type*) ; 
 scalar_t__ sparc64_structure_or_union_p (struct type*) ; 

__attribute__((used)) static void
sparc64_extract_floating_fields (struct regcache *regcache, struct type *type,
				 char *valbuf, int bitpos)
{
  if (sparc64_floating_p (type))
    {
      int len = TYPE_LENGTH (type);
      int regnum;

      if (len == 16)
	{
	  gdb_assert (bitpos == 0 || bitpos == 128);

	  regnum = SPARC64_Q0_REGNUM + bitpos / 128;
	  regcache_cooked_read (regcache, regnum, valbuf + (bitpos / 8));
	}
      else if (len == 8)
	{
	  gdb_assert (bitpos % 64 == 0 && bitpos >= 0 && bitpos < 256);

	  regnum = SPARC64_D0_REGNUM + bitpos / 64;
	  regcache_cooked_read (regcache, regnum, valbuf + (bitpos / 8));
	}
      else
	{
	  gdb_assert (len == 4);
	  gdb_assert (bitpos % 32 == 0 && bitpos >= 0 && bitpos < 256);

	  regnum = SPARC_F0_REGNUM + bitpos / 32;
	  regcache_cooked_read (regcache, regnum, valbuf + (bitpos / 8));
	}
    }
  else if (sparc64_structure_or_union_p (type))
    {
      int i;

      for (i = 0; i < TYPE_NFIELDS (type); i++)
	{
	  struct type *subtype = check_typedef (TYPE_FIELD_TYPE (type, i));
	  int subpos = bitpos + TYPE_FIELD_BITPOS (type, i);

	  sparc64_extract_floating_fields (regcache, subtype, valbuf, subpos);
	}
    }
}