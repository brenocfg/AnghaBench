#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int escaped; int /*<<< orphan*/ * handle_ptr; scalar_t__ prelist_handle_count; } ;
typedef  TYPE_1__ jerryx_handle_scope_t ;
struct TYPE_8__ {struct TYPE_8__* parent; struct TYPE_8__* child; } ;
typedef  TYPE_2__ jerryx_handle_scope_dynamic_t ;
struct TYPE_9__ {scalar_t__ count; TYPE_2__* start; TYPE_1__* prelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  JERRYX_HANDLE_SCOPE_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ JERRYX_SCOPE_PRELIST_SIZE ; 
 TYPE_1__* jerryx_handle_scope_current ; 
 TYPE_4__ jerryx_handle_scope_pool ; 
 TYPE_2__* malloc (int) ; 

jerryx_handle_scope_t *
jerryx_handle_scope_alloc (void)
{
  jerryx_handle_scope_t *scope;
  if (jerryx_handle_scope_pool.count < JERRYX_SCOPE_PRELIST_SIZE)
  {
    scope = jerryx_handle_scope_pool.prelist + jerryx_handle_scope_pool.count;
  }
  else
  {
    jerryx_handle_scope_dynamic_t *dy_scope = malloc (sizeof (jerryx_handle_scope_dynamic_t));
    JERRYX_HANDLE_SCOPE_ASSERT (dy_scope != NULL);
    dy_scope->child = NULL;

    if (jerryx_handle_scope_pool.count != JERRYX_SCOPE_PRELIST_SIZE)
    {
      jerryx_handle_scope_dynamic_t *dy_current = (jerryx_handle_scope_dynamic_t *) jerryx_handle_scope_current;
      dy_scope->parent = dy_current;
      dy_current->child = dy_scope;
    }
    else
    {
      jerryx_handle_scope_pool.start = dy_scope;
      dy_scope->parent = NULL;
    }

    scope = (jerryx_handle_scope_t *) dy_scope;
  }

  scope->prelist_handle_count = 0;
  scope->escaped = false;
  scope->handle_ptr = NULL;

  jerryx_handle_scope_current = scope;
  ++jerryx_handle_scope_pool.count;
  return (jerryx_handle_scope_t *) scope;
}