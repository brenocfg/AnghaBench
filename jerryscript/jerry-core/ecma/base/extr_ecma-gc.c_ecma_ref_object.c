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
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {scalar_t__ type_flags_refs; } ;
typedef  TYPE_1__ ecma_object_t ;

/* Variables and functions */
 scalar_t__ ECMA_OBJECT_MAX_REF ; 
 scalar_t__ ECMA_OBJECT_REF_ONE ; 
 int /*<<< orphan*/  ERR_REF_COUNT_LIMIT ; 
 scalar_t__ JERRY_LIKELY (int) ; 
 int /*<<< orphan*/  jerry_fatal (int /*<<< orphan*/ ) ; 

void
ecma_ref_object (ecma_object_t *object_p) /**< object */
{
  if (JERRY_LIKELY (object_p->type_flags_refs < ECMA_OBJECT_MAX_REF))
  {
    object_p->type_flags_refs = (uint16_t) (object_p->type_flags_refs + ECMA_OBJECT_REF_ONE);
  }
  else
  {
    jerry_fatal (ERR_REF_COUNT_LIMIT);
  }
}