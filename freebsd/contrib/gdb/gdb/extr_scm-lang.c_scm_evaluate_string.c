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
typedef  scalar_t__ LONGEST ;

/* Variables and functions */
 struct value* call_function_by_hand (struct value*,int,struct value**) ; 
 struct value* find_function_in_inferior (char*) ; 
 struct value* value_allocate_space_in_inferior (int) ; 
 scalar_t__ value_as_long (struct value*) ; 
 int /*<<< orphan*/  write_memory (scalar_t__,char*,int) ; 

struct value *
scm_evaluate_string (char *str, int len)
{
  struct value *func;
  struct value *addr = value_allocate_space_in_inferior (len + 1);
  LONGEST iaddr = value_as_long (addr);
  write_memory (iaddr, str, len);
  /* FIXME - should find and pass env */
  write_memory (iaddr + len, "", 1);
  func = find_function_in_inferior ("scm_evstr");
  return call_function_by_hand (func, 1, &addr);
}