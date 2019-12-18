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
struct s390_prologue_data {int dummy; } ;
struct prologue_value {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ pv_definite_yes ; 
 scalar_t__ s390_on_stack (struct prologue_value*,int /*<<< orphan*/ ,struct s390_prologue_data*,struct prologue_value**) ; 

__attribute__((used)) static void
s390_store (struct prologue_value *addr,
            CORE_ADDR size,
            struct prologue_value *value,
	    struct s390_prologue_data *data)
{
  struct prologue_value *stack;

  /* We can do it if it's definitely a reference to something on the stack.  */
  if (s390_on_stack (addr, size, data, &stack) == pv_definite_yes)
    {
      *stack = *value;
      return;
    }

  /* Note: If s390_on_stack returns pv_maybe, you might think we should
     forget our cached values, as any of those might have been hit.

     However, we make the assumption that --since the fields we track
     are save areas private to compiler, and never directly exposed to 
     the user-- every access to our data is explicit.  Hence, every 
     memory access we cannot follow can't hit our data.  */
}