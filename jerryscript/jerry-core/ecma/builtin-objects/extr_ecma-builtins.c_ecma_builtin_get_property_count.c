#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ magic_string_id; } ;
typedef  TYPE_1__ ecma_builtin_property_descriptor_t ;
typedef  size_t ecma_builtin_id_t ;

/* Variables and functions */
 size_t ECMA_BUILTIN_ID__COUNT ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 scalar_t__ LIT_MAGIC_STRING__COUNT ; 
 TYPE_1__** ecma_builtin_property_list_references ; 

__attribute__((used)) static size_t
ecma_builtin_get_property_count (ecma_builtin_id_t builtin_id) /**< built-in ID */
{
  JERRY_ASSERT (builtin_id < ECMA_BUILTIN_ID__COUNT);
  const ecma_builtin_property_descriptor_t *property_list_p = ecma_builtin_property_list_references[builtin_id];

  const ecma_builtin_property_descriptor_t *curr_property_p = property_list_p;

  while (curr_property_p->magic_string_id != LIT_MAGIC_STRING__COUNT)
  {
    curr_property_p++;
  }

  return (size_t) (curr_property_p - property_list_p);
}