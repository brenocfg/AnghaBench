#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_4__* elements; } ;
typedef  TYPE_1__ svn_priority_queue__t ;
struct TYPE_6__ {void const* elts; scalar_t__ nelts; int /*<<< orphan*/  elt_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  apr_array_push (TYPE_4__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_bubble_down (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 

void
svn_priority_queue__push(svn_priority_queue__t *queue,
                         const void *element)
{
  /* we cannot duplicate elements due to potential array re-allocs */
  assert(element && element != queue->elements->elts);

  memcpy(apr_array_push(queue->elements), element, queue->elements->elt_size);
  heap_bubble_down(queue, queue->elements->nelts - 1);
}