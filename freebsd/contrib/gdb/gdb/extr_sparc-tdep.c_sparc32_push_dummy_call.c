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
 int /*<<< orphan*/  SPARC_O7_REGNUM ; 
 int /*<<< orphan*/  SPARC_SP_REGNUM ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  regcache_cooked_write_unsigned (struct regcache*,int /*<<< orphan*/ ,int) ; 
 int sparc32_store_arguments (struct regcache*,int,struct value**,int,int,int) ; 

__attribute__((used)) static CORE_ADDR
sparc32_push_dummy_call (struct gdbarch *gdbarch, CORE_ADDR func_addr,
			 struct regcache *regcache, CORE_ADDR bp_addr,
			 int nargs, struct value **args, CORE_ADDR sp,
			 int struct_return, CORE_ADDR struct_addr)
{
  CORE_ADDR call_pc = (struct_return ? (bp_addr - 12) : (bp_addr - 8));

  /* Set return address.  */
  regcache_cooked_write_unsigned (regcache, SPARC_O7_REGNUM, call_pc);

  /* Set up function arguments.  */
  sp = sparc32_store_arguments (regcache, nargs, args, sp,
				struct_return, struct_addr);

  /* Allocate the 16-word window save area.  */
  sp -= 16 * 4;

  /* Stack should be doubleword aligned at this point.  */
  gdb_assert (sp % 8 == 0);

  /* Finally, update the stack pointer.  */
  regcache_cooked_write_unsigned (regcache, SPARC_SP_REGNUM, sp);

  return sp;
}