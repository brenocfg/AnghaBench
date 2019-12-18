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
struct gdbarch {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  store_unsigned_integer (char*,int,int) ; 
 scalar_t__ using_struct_return (struct type*,int) ; 
 int /*<<< orphan*/  write_memory (scalar_t__,char*,int) ; 

__attribute__((used)) static CORE_ADDR
sparc32_push_dummy_code (struct gdbarch *gdbarch, CORE_ADDR sp,
			 CORE_ADDR funcaddr, int using_gcc,
			 struct value **args, int nargs,
			 struct type *value_type,
			 CORE_ADDR *real_pc, CORE_ADDR *bp_addr)
{
  *bp_addr = sp - 4;
  *real_pc = funcaddr;

  if (using_struct_return (value_type, using_gcc))
    {
      char buf[4];

      /* This is an UNIMP instruction.  */
      store_unsigned_integer (buf, 4, TYPE_LENGTH (value_type) & 0x1fff);
      write_memory (sp - 8, buf, 4);
      return sp - 8;
    }

  return sp - 4;
}