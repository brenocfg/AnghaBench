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
 int /*<<< orphan*/  SPARC_F0_REGNUM ; 
 int /*<<< orphan*/  SPARC_F1_REGNUM ; 
 int /*<<< orphan*/  SPARC_O0_REGNUM ; 
 int /*<<< orphan*/  SPARC_O1_REGNUM ; 
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 
 int /*<<< orphan*/  regcache_cooked_read (struct regcache*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sparc_floating_p (struct type*) ; 
 int sparc_integral_or_pointer_p (struct type*) ; 
 int /*<<< orphan*/  sparc_structure_or_union_p (struct type*) ; 

__attribute__((used)) static void
sparc32_extract_return_value (struct type *type, struct regcache *regcache,
			      void *valbuf)
{
  int len = TYPE_LENGTH (type);
  char buf[8];

  gdb_assert (!sparc_structure_or_union_p (type));
  gdb_assert (!(sparc_floating_p (type) && len == 16));

  if (sparc_floating_p (type))
    {
      /* Floating return values.  */
      regcache_cooked_read (regcache, SPARC_F0_REGNUM, buf);
      if (len > 4)
	regcache_cooked_read (regcache, SPARC_F1_REGNUM, buf + 4);
      memcpy (valbuf, buf, len);
    }
  else
    {
      /* Integral and pointer return values.  */
      gdb_assert (sparc_integral_or_pointer_p (type));

      regcache_cooked_read (regcache, SPARC_O0_REGNUM, buf);
      if (len > 4)
	{
	  regcache_cooked_read (regcache, SPARC_O1_REGNUM, buf + 4);
	  gdb_assert (len == 8);
	  memcpy (valbuf, buf, 8);
	}
      else
	{
	  /* Just stripping off any unused bytes should preserve the
	     signed-ness just fine.  */
	  memcpy (valbuf, buf + 4 - len, len);
	}
    }
}