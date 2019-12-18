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
struct regcache {int dummy; } ;
struct gdbarch {int dummy; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int BIAS ; 
 int /*<<< orphan*/  SPARC_O7_REGNUM ; 
 int /*<<< orphan*/  SPARC_SP_REGNUM ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  regcache_cooked_write_unsigned (struct regcache*,int /*<<< orphan*/ ,int) ; 
 int sparc64_store_arguments (struct regcache*,int,struct value**,int,int,int) ; 

__attribute__((used)) static CORE_ADDR
sparc64_push_dummy_call (struct gdbarch *gdbarch, CORE_ADDR func_addr,
			 struct regcache *regcache, CORE_ADDR bp_addr,
			 int nargs, struct value **args, CORE_ADDR sp,
			 int struct_return, CORE_ADDR struct_addr)
{
  /* Set return address.  */
  regcache_cooked_write_unsigned (regcache, SPARC_O7_REGNUM, bp_addr - 8);

  /* Set up function arguments.  */
  sp = sparc64_store_arguments (regcache, nargs, args, sp,
				struct_return, struct_addr);

  /* Allocate the register save area.  */
  sp -= 16 * 8;

  /* Stack should be 16-byte aligned at this point.  */
  gdb_assert ((sp + BIAS) % 16 == 0);

  /* Finally, update the stack pointer.  */
  regcache_cooked_write_unsigned (regcache, SPARC_SP_REGNUM, sp);

  return sp;
}