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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  const apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * svn_string_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_ns_prop(apr_hash_t *ns_props,
            const char *ns, const char *name,
            const svn_string_t *val, apr_pool_t *result_pool)
{
  apr_hash_t *props = svn_hash_gets(ns_props, ns);

  if (!props)
    {
      props = apr_hash_make(result_pool);
      ns = apr_pstrdup(result_pool, ns);
      svn_hash_sets(ns_props, ns, props);
    }

  if (val)
    {
      name = apr_pstrdup(result_pool, name);
      val = svn_string_dup(val, result_pool);
    }

  svn_hash_sets(props, name, val);
}