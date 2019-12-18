#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* recycler; TYPE_2__* source; } ;
typedef  TYPE_1__ svn_temp_serializer__context_t ;
struct TYPE_6__ {struct TYPE_6__* upper; } ;
typedef  TYPE_2__ source_stack_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 

void
svn_temp_serializer__pop(svn_temp_serializer__context_t *context)
{
  source_stack_t *old = context->source;

  /* we may pop the original struct but not further */
  assert(context->source);

  /* one level up the structure stack */
  context->source = context->source->upper;

  /* put the old stack element into the recycler for later reuse */
  old->upper = context->recycler;
  context->recycler = old;
}