#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_12__ {scalar_t__ apr_err; int /*<<< orphan*/  message; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ENTRY_NOT_FOUND ; 
 scalar_t__ SVN_ERR_WC_NOT_WORKING_COPY ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 TYPE_2__* svn_error_create (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 scalar_t__ svn_node_dir ; 
 TYPE_2__* svn_wc__db_is_switched (int*,int*,scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_is_wc_root2(svn_boolean_t *wc_root,
                   svn_wc_context_t *wc_ctx,
                   const char *local_abspath,
                   apr_pool_t *scratch_pool)
{
  svn_boolean_t is_root;
  svn_boolean_t is_switched;
  svn_node_kind_t kind;
  svn_error_t *err;
  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  err = svn_wc__db_is_switched(&is_root, &is_switched, &kind,
                               wc_ctx->db, local_abspath, scratch_pool);

  if (err)
    {
      if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND &&
          err->apr_err != SVN_ERR_WC_NOT_WORKING_COPY)
        return svn_error_trace(err);

      return svn_error_create(SVN_ERR_ENTRY_NOT_FOUND, err, err->message);
    }

  *wc_root = is_root || (kind == svn_node_dir && is_switched);

  return SVN_NO_ERROR;
}