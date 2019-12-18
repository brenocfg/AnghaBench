#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  jval; struct TYPE_6__* sibling; } ;
typedef  TYPE_1__ jerryx_handle_t ;
typedef  TYPE_2__* jerryx_handle_scope ;
typedef  int /*<<< orphan*/  jerry_value_t ;
struct TYPE_7__ {size_t prelist_handle_count; TYPE_1__* handle_ptr; int /*<<< orphan*/ * handle_prelist; } ;

/* Variables and functions */
 size_t JERRYX_HANDLE_PRELIST_SIZE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

jerry_value_t
jerryx_handle_scope_add_handle_to (jerryx_handle_t *handle, jerryx_handle_scope scope)
{
  size_t prelist_handle_count = scope->prelist_handle_count;
  if (prelist_handle_count < JERRYX_HANDLE_PRELIST_SIZE)
  {
    ++scope->prelist_handle_count;
    jerry_value_t jval = handle->jval;
    free (handle);
    scope->handle_prelist[prelist_handle_count] = jval;
    return jval;
  }

  handle->sibling = scope->handle_ptr;
  scope->handle_ptr = handle;
  return handle->jval;
}