#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int (* compare_func ) (void const*,void const*) ;TYPE_2__* elements; } ;
typedef  TYPE_1__ svn_priority_queue__t ;
struct TYPE_8__ {int nelts; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ apr_array_header_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  heap_bubble_up (TYPE_1__*,int) ; 

svn_priority_queue__t *
svn_priority_queue__create(apr_array_header_t *elements,
                           int (*compare_func)(const void *, const void *))
{
  int i;

  svn_priority_queue__t *queue = apr_pcalloc(elements->pool, sizeof(*queue));
  queue->elements = elements;
  queue->compare_func = compare_func;

  for (i = elements->nelts / 2; i >= 0; --i)
    heap_bubble_up(queue, i);

  return queue;
}