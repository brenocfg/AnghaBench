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
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int SPARC32_D0_REGNUM ; 
 int SPARC32_D30_REGNUM ; 
 int SPARC32_NPC_REGNUM ; 
 int SPARC32_PC_REGNUM ; 
 int SPARC_F0_REGNUM ; 
 int SPARC_F31_REGNUM ; 
 int SPARC_FP_REGNUM ; 
 int SPARC_SP_REGNUM ; 
 struct type* builtin_type_double ; 
 struct type* builtin_type_float ; 
 struct type* builtin_type_int32 ; 
 struct type* builtin_type_void_data_ptr ; 
 struct type* builtin_type_void_func_ptr ; 

__attribute__((used)) static struct type *
sparc32_register_type (struct gdbarch *gdbarch, int regnum)
{
  if (regnum >= SPARC_F0_REGNUM && regnum <= SPARC_F31_REGNUM)
    return builtin_type_float;

  if (regnum >= SPARC32_D0_REGNUM && regnum <= SPARC32_D30_REGNUM)
    return builtin_type_double;

  if (regnum == SPARC_SP_REGNUM || regnum == SPARC_FP_REGNUM)
    return builtin_type_void_data_ptr;

  if (regnum == SPARC32_PC_REGNUM || regnum == SPARC32_NPC_REGNUM)
    return builtin_type_void_func_ptr;

  return builtin_type_int32;
}