#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_9__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct svn_wc__shim_fetch_baton_t {int /*<<< orphan*/  db; scalar_t__ fetch_base; int /*<<< orphan*/  base_abspath; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 TYPE_1__* svn_wc__db_base_get_props (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__db_read_props (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__fetch_props_func(apr_hash_t **props,
                         void *baton,
                         const char *path,
                         svn_revnum_t base_revision,
                         apr_pool_t *result_pool,
                         apr_pool_t *scratch_pool)
{
  struct svn_wc__shim_fetch_baton_t *sfb = baton;
  const char *local_abspath = svn_dirent_join(sfb->base_abspath, path,
                                              scratch_pool);
  svn_error_t *err;

  if (sfb->fetch_base)
    err = svn_wc__db_base_get_props(props, sfb->db, local_abspath, result_pool,
                                    scratch_pool);
  else
    err = svn_wc__db_read_props(props, sfb->db, local_abspath,
                                result_pool, scratch_pool);

  /* If the path doesn't exist, just return an empty set of props. */
  if (err && err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
    {
      svn_error_clear(err);
      *props = apr_hash_make(result_pool);
    }
  else if (err)
    return svn_error_trace(err);

  return SVN_NO_ERROR;
}