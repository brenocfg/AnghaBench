#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jerryx_module_resolver_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* init_cb ) (void*) ;int /*<<< orphan*/  (* deinit_cb ) (void*) ;} ;

/* Variables and functions */
 void* jerry_get_context_data (TYPE_1__*) ; 
 scalar_t__ jerry_value_is_undefined (int /*<<< orphan*/  const) ; 
 TYPE_1__ jerryx_module_manager ; 
 int /*<<< orphan*/  jerryx_module_resolve_local (int /*<<< orphan*/  const,int /*<<< orphan*/  const**,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 

void
jerryx_module_clear_cache (const jerry_value_t name, /**< name of the module to remove, or undefined */
                           const jerryx_module_resolver_t **resolvers_p, /**< list of resolvers */
                           size_t resolver_count) /**< number of resolvers in @p resolvers */
{
  void *instances_p = jerry_get_context_data (&jerryx_module_manager);

  if (jerry_value_is_undefined (name))
  {
    /* We were requested to clear the entire cache, so we bounce the context data in the most agnostic way possible. */
    jerryx_module_manager.deinit_cb (instances_p);
    jerryx_module_manager.init_cb (instances_p);
    return;
  }

  /* Delete the requested module from the cache if it's there. */
  jerryx_module_resolve_local (name, resolvers_p, resolver_count, NULL);
}