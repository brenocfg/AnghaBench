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
struct section_table {int /*<<< orphan*/  the_bfd_section; int /*<<< orphan*/  bfd; } ;
struct s390_prologue_data {int dummy; } ;
struct prologue_value {scalar_t__ kind; int /*<<< orphan*/  k; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int SEC_READONLY ; 
 int bfd_get_section_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_target ; 
 scalar_t__ pv_constant ; 
 scalar_t__ pv_definite_yes ; 
 int /*<<< orphan*/  pv_set_to_constant (struct prologue_value*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pv_set_to_unknown (struct prologue_value*) ; 
 int /*<<< orphan*/  read_memory_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ s390_on_stack (struct prologue_value*,int /*<<< orphan*/ ,struct s390_prologue_data*,struct prologue_value**) ; 
 struct section_table* target_section_by_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
s390_load (struct prologue_value *addr,
	   CORE_ADDR size,
	   struct prologue_value *value,
	   struct s390_prologue_data *data)
{
  struct prologue_value *stack;

  /* If it's a load from an in-line constant pool, then we can
     simulate that, under the assumption that the code isn't
     going to change between the time the processor actually
     executed it creating the current frame, and the time when
     we're analyzing the code to unwind past that frame.  */
  if (addr->kind == pv_constant)
    {
      struct section_table *secp;
      secp = target_section_by_addr (&current_target, addr->k);
      if (secp != NULL
          && (bfd_get_section_flags (secp->bfd, secp->the_bfd_section)
              & SEC_READONLY))
	{
          pv_set_to_constant (value, read_memory_integer (addr->k, size));
	  return;
	}
    }

  /* If it's definitely a reference to something on the stack, 
     we can do that.  */
  if (s390_on_stack (addr, size, data, &stack) == pv_definite_yes)
    {
      *value = *stack;
      return;
    }

  /* Otherwise, we don't know the value.  */
  pv_set_to_unknown (value);
}