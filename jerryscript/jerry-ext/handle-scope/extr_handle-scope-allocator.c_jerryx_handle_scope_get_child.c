#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jerryx_handle_scope_t ;
struct TYPE_3__ {struct TYPE_3__* child; } ;
typedef  TYPE_1__ jerryx_handle_scope_dynamic_t ;
struct TYPE_4__ {int count; int /*<<< orphan*/ * prelist; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/ * JERRYX_HANDLE_SCOPE_POOL_PRELIST_LAST ; 
 long JERRYX_HANDLE_SCOPE_PRELIST_IDX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jerryx_handle_scope_is_in_prelist (int /*<<< orphan*/ *) ; 
 TYPE_2__ jerryx_handle_scope_pool ; 
 int /*<<< orphan*/  jerryx_handle_scope_root ; 

jerryx_handle_scope_t *
jerryx_handle_scope_get_child (jerryx_handle_scope_t *scope)
{
  if (scope == &jerryx_handle_scope_root)
  {
    if (jerryx_handle_scope_pool.count > 0)
    {
      return jerryx_handle_scope_pool.prelist;
    }
    return NULL;
  }
  if (!jerryx_handle_scope_is_in_prelist (scope))
  {
    jerryx_handle_scope_dynamic_t *child = ((jerryx_handle_scope_dynamic_t *) scope)->child;
    return (jerryx_handle_scope_t *) child;
  }
  if (scope == JERRYX_HANDLE_SCOPE_POOL_PRELIST_LAST)
  {
    return (jerryx_handle_scope_t *) jerryx_handle_scope_pool.start;
  }
  long idx = JERRYX_HANDLE_SCOPE_PRELIST_IDX (scope);
  if (idx < 0)
  {
    return NULL;
  }
  if ((unsigned long) idx >= jerryx_handle_scope_pool.count - 1)
  {
    return NULL;
  }
  return jerryx_handle_scope_pool.prelist + idx + 1;
}