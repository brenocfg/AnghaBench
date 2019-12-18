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
struct TYPE_2__ {int string_lower_bound; int /*<<< orphan*/ * string_char_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  VALUE_CONTENTS_RAW (struct value*) ; 
 struct value* allocate_value (struct type*) ; 
 int /*<<< orphan*/  builtin_type_int ; 
 struct type* create_array_type (struct type*,int /*<<< orphan*/ ,struct type*) ; 
 struct type* create_range_type (struct type*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* current_language ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int strlen (char*) ; 

struct value *
value_from_string (char *ptr)
{
  struct value *val;
  int len = strlen (ptr);
  int lowbound = current_language->string_lower_bound;
  struct type *rangetype =
  create_range_type ((struct type *) NULL,
		     builtin_type_int,
		     lowbound, len + lowbound - 1);
  struct type *stringtype =
  create_array_type ((struct type *) NULL,
		     *current_language->string_char_type,
		     rangetype);

  val = allocate_value (stringtype);
  memcpy (VALUE_CONTENTS_RAW (val), ptr, len);
  return val;
}