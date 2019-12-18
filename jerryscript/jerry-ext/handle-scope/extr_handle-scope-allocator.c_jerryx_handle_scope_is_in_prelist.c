#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jerryx_handle_scope_t ;
struct TYPE_2__ {int /*<<< orphan*/ * prelist; } ;

/* Variables and functions */
 int JERRYX_SCOPE_PRELIST_SIZE ; 
 TYPE_1__ jerryx_handle_scope_pool ; 

__attribute__((used)) static bool
jerryx_handle_scope_is_in_prelist (jerryx_handle_scope_t *scope)
{
  return (jerryx_handle_scope_pool.prelist <= scope)
  && (scope <= (jerryx_handle_scope_pool.prelist + JERRYX_SCOPE_PRELIST_SIZE - 1));
}