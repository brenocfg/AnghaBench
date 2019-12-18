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
struct TYPE_4__ {void* elts; scalar_t__ nelts; } ;

/* Variables and functions */

void *
svn_priority_queue__peek(svn_priority_queue__t *queue)
{
  return queue->elements->nelts ? queue->elements->elts : NULL;
}