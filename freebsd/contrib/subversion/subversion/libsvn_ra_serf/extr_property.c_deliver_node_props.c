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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_string_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
deliver_node_props(void *baton,
                  const char *path,
                  const char *ns,
                  const char *name,
                  const svn_string_t *value,
                  apr_pool_t *scratch_pool)
{
  apr_hash_t *nss = baton;
  apr_hash_t *props;
  apr_pool_t *result_pool = apr_hash_pool_get(nss);

  props = svn_hash_gets(nss, ns);

  if (!props)
    {
      props = apr_hash_make(result_pool);

      ns = apr_pstrdup(result_pool, ns);
      svn_hash_sets(nss, ns, props);
    }

  name = apr_pstrdup(result_pool, name);
  svn_hash_sets(props, name, svn_string_dup(value, result_pool));

  return SVN_NO_ERROR;
}