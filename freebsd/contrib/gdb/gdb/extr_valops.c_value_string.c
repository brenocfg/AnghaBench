#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct value {int dummy; } ;
struct type {int dummy; } ;
struct TYPE_2__ {int string_lower_bound; scalar_t__ c_style_arrays; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  VALUE_CONTENTS_RAW (struct value*) ; 
 int /*<<< orphan*/  allocate_space_in_inferior (int) ; 
 struct value* allocate_value (struct type*) ; 
 int /*<<< orphan*/  builtin_type_int ; 
 struct type* create_range_type (struct type*,int /*<<< orphan*/ ,int,int) ; 
 struct type* create_string_type (struct type*,struct type*) ; 
 TYPE_1__* current_language ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct value* value_at_lazy (struct type*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_memory (int /*<<< orphan*/ ,char*,int) ; 

struct value *
value_string (char *ptr, int len)
{
  struct value *val;
  int lowbound = current_language->string_lower_bound;
  struct type *rangetype = create_range_type ((struct type *) NULL,
					      builtin_type_int,
					      lowbound, len + lowbound - 1);
  struct type *stringtype
  = create_string_type ((struct type *) NULL, rangetype);
  CORE_ADDR addr;

  if (current_language->c_style_arrays == 0)
    {
      val = allocate_value (stringtype);
      memcpy (VALUE_CONTENTS_RAW (val), ptr, len);
      return val;
    }


  /* Allocate space to store the string in the inferior, and then
     copy LEN bytes from PTR in gdb to that address in the inferior. */

  addr = allocate_space_in_inferior (len);
  write_memory (addr, ptr, len);

  val = value_at_lazy (stringtype, addr, NULL);
  return (val);
}