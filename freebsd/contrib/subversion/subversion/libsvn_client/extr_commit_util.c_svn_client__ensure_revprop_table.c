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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_CLIENT_PROPERTY_NAME ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_LOG ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_prop_has_svn_prop (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_create (char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__ensure_revprop_table(apr_hash_t **revprop_table_out,
                                 const apr_hash_t *revprop_table_in,
                                 const char *log_msg,
                                 svn_client_ctx_t *ctx,
                                 apr_pool_t *pool)
{
  apr_hash_t *new_revprop_table;
  if (revprop_table_in)
    {
      if (svn_prop_has_svn_prop(revprop_table_in, pool))
        return svn_error_create(SVN_ERR_CLIENT_PROPERTY_NAME, NULL,
                                _("Standard properties can't be set "
                                  "explicitly as revision properties"));
      new_revprop_table = apr_hash_copy(pool, revprop_table_in);
    }
  else
    {
      new_revprop_table = apr_hash_make(pool);
    }
  svn_hash_sets(new_revprop_table, SVN_PROP_REVISION_LOG,
                svn_string_create(log_msg, pool));
  *revprop_table_out = new_revprop_table;
  return SVN_NO_ERROR;
}