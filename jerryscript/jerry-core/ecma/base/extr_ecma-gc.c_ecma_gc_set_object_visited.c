#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
struct TYPE_4__ {int type_flags_refs; } ;
typedef  TYPE_1__ ecma_object_t ;

/* Variables and functions */
 int ECMA_OBJECT_NON_VISITED ; 
 int ECMA_OBJECT_REF_ONE ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 scalar_t__ JERRY_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_gc_mark (TYPE_1__*) ; 
 int /*<<< orphan*/  ecma_gc_mark_recursion_limit ; 

__attribute__((used)) static void
ecma_gc_set_object_visited (ecma_object_t *object_p) /**< object */
{
  if (object_p->type_flags_refs >= ECMA_OBJECT_NON_VISITED)
  {
#if (JERRY_GC_MARK_LIMIT != 0)
    if (JERRY_CONTEXT (ecma_gc_mark_recursion_limit) != 0)
    {
      JERRY_CONTEXT (ecma_gc_mark_recursion_limit)--;
      /* Set the reference count of gray object to 0 */
      object_p->type_flags_refs = (uint16_t) (object_p->type_flags_refs & (ECMA_OBJECT_REF_ONE - 1));
      ecma_gc_mark (object_p);
      JERRY_CONTEXT (ecma_gc_mark_recursion_limit)++;
    }
    else
    {
      /* Set the reference count of the non-marked gray object to 1 */
      object_p->type_flags_refs = (uint16_t) (object_p->type_flags_refs & ((ECMA_OBJECT_REF_ONE << 1) - 1));
      JERRY_ASSERT (object_p->type_flags_refs >= ECMA_OBJECT_REF_ONE);
    }
#else /* (JERRY_GC_MARK_LIMIT == 0) */
    /* Set the reference count of gray object to 0 */
    object_p->type_flags_refs = (uint16_t) (object_p->type_flags_refs & (ECMA_OBJECT_REF_ONE - 1));
#endif /* (JERRY_GC_MARK_LIMIT != 0) */
  }
}