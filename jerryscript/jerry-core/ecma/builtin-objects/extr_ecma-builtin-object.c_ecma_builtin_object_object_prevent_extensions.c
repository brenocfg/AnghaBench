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
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  ecma_make_object_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_ref_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_set_object_extensible (int /*<<< orphan*/ *,int) ; 

ecma_value_t
ecma_builtin_object_object_prevent_extensions (ecma_object_t *obj_p) /**< routine's argument */
{
  ecma_set_object_extensible (obj_p, false);
  ecma_ref_object (obj_p);

  return ecma_make_object_value (obj_p);
}