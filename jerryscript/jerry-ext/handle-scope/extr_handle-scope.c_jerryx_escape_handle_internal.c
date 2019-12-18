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
struct TYPE_7__ {scalar_t__ jval; struct TYPE_7__* sibling; } ;
typedef  TYPE_1__ jerryx_handle_t ;
typedef  int /*<<< orphan*/  jerryx_handle_scope_status ;
typedef  int /*<<< orphan*/ * jerryx_handle_scope ;
typedef  TYPE_2__* jerryx_escapable_handle_scope ;
typedef  scalar_t__ jerry_value_t ;
struct TYPE_8__ {int escaped; size_t prelist_handle_count; scalar_t__* handle_prelist; TYPE_1__* handle_ptr; } ;

/* Variables and functions */
 size_t JERRYX_HANDLE_PRELIST_SIZE ; 
 int /*<<< orphan*/  jerryx_create_handle_in_scope (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jerryx_escape_called_twice ; 
 scalar_t__ jerryx_hand_scope_escape_handle_from_prelist (TYPE_2__*,size_t) ; 
 scalar_t__ jerryx_handle_scope_add_handle_to (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jerryx_handle_scope_get_parent (TYPE_2__*) ; 
 int /*<<< orphan*/  jerryx_handle_scope_mismatch ; 
 int /*<<< orphan*/  jerryx_handle_scope_ok ; 

jerryx_handle_scope_status
jerryx_escape_handle_internal (jerryx_escapable_handle_scope scope,
                               jerry_value_t escapee,
                               jerry_value_t *result,
                               bool should_promote)
{
  if (scope->escaped)
  {
    return jerryx_escape_called_twice;
  }

  jerryx_handle_scope parent = jerryx_handle_scope_get_parent (scope);
  if (parent == NULL)
  {
    return jerryx_handle_scope_mismatch;
  }

  bool found = false;
  {
    size_t found_idx = 0;
    size_t prelist_count = scope->prelist_handle_count;
    /**
     * Search prelist in a reversed order since last added handle
     * is possible the one to be escaped
     */
    for (size_t idx_plus_1 = prelist_count; idx_plus_1 > 0; --idx_plus_1)
    {
      if (escapee == scope->handle_prelist[idx_plus_1 - 1])
      {
        found = true;
        found_idx = idx_plus_1 - 1;
        break;
      }
    }

    if (found)
    {
      *result = jerryx_hand_scope_escape_handle_from_prelist (scope, found_idx);

      --scope->prelist_handle_count;
      if (should_promote)
      {
        scope->escaped = true;
        /**
         * Escape handle to parent scope
         */
        jerryx_create_handle_in_scope (*result, jerryx_handle_scope_get_parent (scope));
      }
      return jerryx_handle_scope_ok;
    }
  };

  if (scope->prelist_handle_count <= JERRYX_HANDLE_PRELIST_SIZE && scope->handle_ptr == NULL)
  {
    return jerryx_handle_scope_mismatch;
  }

  /**
   * Handle chain list is already in an reversed order,
   * search through it as it is
   */
  jerryx_handle_t *handle = scope->handle_ptr;
  jerryx_handle_t *memo_handle = NULL;
  jerryx_handle_t *found_handle = NULL;
  while (!found)
  {
    if (handle == NULL)
    {
      return jerryx_handle_scope_mismatch;
    }
    if (handle->jval != escapee)
    {
      memo_handle = handle;
      handle = handle->sibling;
      continue;
    }
    /**
     * Remove found handle from current scope's handle chain
     */
    found = true;
    found_handle = handle;
    if (memo_handle == NULL)
    {
      // found handle is the first handle in heap
      scope->handle_ptr = found_handle->sibling;
    }
    else
    {
      memo_handle->sibling = found_handle->sibling;
    }
  }

  if (should_promote)
  {
    /**
     * Escape handle to parent scope
     */
    *result = jerryx_handle_scope_add_handle_to (found_handle, parent);
  }

  if (should_promote)
  {
    scope->escaped = true;
  }
  return jerryx_handle_scope_ok;
}