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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  VALUE_CONTENTS_RAW (struct value*) ; 
 struct value* allocate_value (struct type*) ; 
 int /*<<< orphan*/  store_typed_address (int /*<<< orphan*/ ,struct type*,int /*<<< orphan*/ ) ; 

struct value *
value_from_pointer (struct type *type, CORE_ADDR addr)
{
  struct value *val = allocate_value (type);
  store_typed_address (VALUE_CONTENTS_RAW (val), type, addr);
  return val;
}