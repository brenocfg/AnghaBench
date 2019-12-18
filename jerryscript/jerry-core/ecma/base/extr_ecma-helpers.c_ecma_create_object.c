#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int ecma_object_type_t ;
struct TYPE_10__ {int /*<<< orphan*/  prototype_cp; } ;
struct TYPE_9__ {int /*<<< orphan*/  property_list_cp; } ;
struct TYPE_11__ {TYPE_2__ u2; TYPE_1__ u1; scalar_t__ type_flags_refs; } ;
typedef  TYPE_3__ ecma_object_t ;

/* Variables and functions */
 int ECMA_OBJECT_FLAG_EXTENSIBLE ; 
 int /*<<< orphan*/  ECMA_SET_POINTER (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  JMEM_CP_NULL ; 
 scalar_t__ ecma_alloc_extended_object (size_t) ; 
 TYPE_3__* ecma_alloc_object () ; 
 int /*<<< orphan*/  ecma_init_gc_info (TYPE_3__*) ; 

ecma_object_t *
ecma_create_object (ecma_object_t *prototype_object_p, /**< pointer to prototybe of the object (or NULL) */
                    size_t ext_object_size, /**< size of extended objects */
                    ecma_object_type_t type) /**< object type */
{
  ecma_object_t *new_object_p;

  if (ext_object_size > 0)
  {
    new_object_p = (ecma_object_t *) ecma_alloc_extended_object (ext_object_size);
  }
  else
  {
    new_object_p = ecma_alloc_object ();
  }

  new_object_p->type_flags_refs = (uint16_t) (type | ECMA_OBJECT_FLAG_EXTENSIBLE);

  ecma_init_gc_info (new_object_p);

  new_object_p->u1.property_list_cp = JMEM_CP_NULL;

  ECMA_SET_POINTER (new_object_p->u2.prototype_cp, prototype_object_p);

  return new_object_p;
}