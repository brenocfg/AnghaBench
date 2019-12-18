#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* elements; } ;
typedef  TYPE_2__ svn_priority_queue__t ;
typedef  int apr_size_t ;
struct TYPE_4__ {char* elts; int elt_size; } ;

/* Variables and functions */

__attribute__((used)) static void
heap_swap(svn_priority_queue__t *queue,
          apr_size_t lhs,
          apr_size_t rhs)
{
  int i;
  char *lhs_value = queue->elements->elts + lhs * queue->elements->elt_size;
  char *rhs_value = queue->elements->elts + rhs * queue->elements->elt_size;

  for (i = 0; i < queue->elements->elt_size; ++i)
    {
      char temp = lhs_value[i];
      lhs_value[i] = rhs_value[i];
      rhs_value[i] = temp;
    }
}