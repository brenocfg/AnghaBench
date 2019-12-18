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
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 char* svn_ra_serf__svnname_from_wirename (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__deliver_svn_props(void *baton,
                               const char *path,
                               const char *ns,
                               const char *name,
                               const svn_string_t *value,
                               apr_pool_t *scratch_pool)
{
  apr_hash_t *props = baton;
  apr_pool_t *result_pool = apr_hash_pool_get(props);
  const char *prop_name;

  prop_name = svn_ra_serf__svnname_from_wirename(ns, name, result_pool);
  if (prop_name == NULL)
    return SVN_NO_ERROR;

  svn_hash_sets(props, prop_name, svn_string_dup(value, result_pool));

  return SVN_NO_ERROR;
}