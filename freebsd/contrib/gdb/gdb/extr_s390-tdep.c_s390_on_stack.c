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
struct prologue_value {int dummy; } ;
struct s390_prologue_data {int gpr_size; int fpr_size; struct prologue_value back_chain; struct prologue_value* spill; struct prologue_value* gpr; } ;
typedef  enum pv_boolean { ____Placeholder_pv_boolean } pv_boolean ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 size_t S390_R0_REGNUM ; 
 size_t S390_SP_REGNUM ; 
 int pv_definite_no ; 
 int pv_definite_yes ; 
 int pv_is_array_ref (struct prologue_value*,int /*<<< orphan*/ ,struct prologue_value*,int,int,int*) ; 
 int pv_maybe ; 
 int /*<<< orphan*/  pv_set_to_register (struct prologue_value*,size_t,int) ; 

__attribute__((used)) static enum pv_boolean
s390_on_stack (struct prologue_value *addr,
               CORE_ADDR size,
	       struct s390_prologue_data *data,
               struct prologue_value **stack)
{
  struct prologue_value gpr_spill_addr;
  struct prologue_value fpr_spill_addr;
  struct prologue_value back_chain_addr;  
  int i;
  enum pv_boolean b;

  /* Construct the addresses of the spill arrays and the back chain.  */
  pv_set_to_register (&gpr_spill_addr, S390_SP_REGNUM, 2 * data->gpr_size);
  pv_set_to_register (&fpr_spill_addr, S390_SP_REGNUM, 16 * data->gpr_size);
  back_chain_addr = data->gpr[S390_SP_REGNUM - S390_R0_REGNUM];

  /* We have to check for GPR and FPR references using two separate
     calls to pv_is_array_ref, since the GPR and FPR spill slots are
     different sizes.  (SPILL is an array, but the thing it tracks
     isn't really an array.)  */

  /* Was it a reference to the GPR spill array?  */
  b = pv_is_array_ref (addr, size, &gpr_spill_addr, 14, data->gpr_size, &i);
  if (b == pv_definite_yes)
    {
      *stack = &data->spill[i];
      return pv_definite_yes;
    }
  if (b == pv_maybe)
    return pv_maybe;

  /* Was it a reference to the FPR spill array?  */
  b = pv_is_array_ref (addr, size, &fpr_spill_addr, 4, data->fpr_size, &i);
  if (b == pv_definite_yes)
    {
      *stack = &data->spill[14 + i];
      return pv_definite_yes;
    }
  if (b == pv_maybe)
    return pv_maybe;

  /* Was it a reference to the back chain?
     This isn't quite right.  We ought to check whether we have
     actually allocated any new frame at all.  */
  b = pv_is_array_ref (addr, size, &back_chain_addr, 1, data->gpr_size, &i);
  if (b == pv_definite_yes)
    {
      *stack = &data->back_chain;
      return pv_definite_yes;
    }
  if (b == pv_maybe)
    return pv_maybe;

  /* All the above queries returned definite 'no's.  */
  return pv_definite_no;
}