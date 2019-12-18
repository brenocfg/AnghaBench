#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  jerryx_module_resolver_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  jerryx_module_resolve_local (int /*<<< orphan*/  const,int /*<<< orphan*/  const**,size_t,int /*<<< orphan*/ *) ; 

jerry_value_t
jerryx_module_resolve (const jerry_value_t name, /**< name of the module to load */
                       const jerryx_module_resolver_t **resolvers_p, /**< list of resolvers */
                       size_t resolver_count) /**< number of resolvers in @p resolvers */
{
  /* Set to zero to circumvent fatal warning. */
  jerry_value_t ret = 0;
  jerryx_module_resolve_local (name, resolvers_p, resolver_count, &ret);
  return ret;
}