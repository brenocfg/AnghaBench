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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ SPARC_F0_REGNUM ; 
 scalar_t__ SPARC_O0_REGNUM ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_UNION ; 
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_cooked_write (struct regcache*,scalar_t__,char*) ; 
 scalar_t__ sparc64_floating_p (struct type*) ; 
 int sparc64_integral_or_pointer_p (struct type*) ; 
 int /*<<< orphan*/  sparc64_store_floating_fields (struct regcache*,struct type*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sparc64_structure_or_union_p (struct type*) ; 

__attribute__((used)) static void
sparc64_store_return_value (struct type *type, struct regcache *regcache,
			    const void *valbuf)
{
  int len = TYPE_LENGTH (type);
  char buf[16];
  int i;

  if (sparc64_structure_or_union_p (type))
    {
      /* Structure or Union return values.  */
      gdb_assert (len <= 32);

      /* Simplify matters by storing the complete value (including
         floating members) into %o0 and %o1.  Floating members are
         also store in the appropriate floating-point registers.  */
      memset (buf, 0, sizeof (buf));
      memcpy (buf, valbuf, len);
      for (i = 0; i < ((len + 7) / 8); i++)
	regcache_cooked_write (regcache, SPARC_O0_REGNUM + i, buf + i * 8);
      if (TYPE_CODE (type) != TYPE_CODE_UNION)
	sparc64_store_floating_fields (regcache, type, buf, 0, 0);
    }
  else if (sparc64_floating_p (type))
    {
      /* Floating return values.  */
      memcpy (buf, valbuf, len);
      for (i = 0; i < len / 4; i++)
	regcache_cooked_write (regcache, SPARC_F0_REGNUM + i, buf + i * 4);
    }
  else
    {
      /* Integral and pointer return values.  */
      gdb_assert (sparc64_integral_or_pointer_p (type));

      /* ??? Do we need to do any sign-extension here?  */
      memset (buf, 0, 8);
      memcpy (buf + 8 - len, valbuf, len);
      regcache_cooked_write (regcache, SPARC_O0_REGNUM, buf);
    }
}