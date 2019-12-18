#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int svn_node_kind_t ;
struct TYPE_11__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
#define  svn_node_dir 130 
#define  svn_node_file 129 
 int svn_node_none ; 
#define  svn_node_symlink 128 
 int svn_node_unknown ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_external_read (scalar_t__*,int*,char const**,char const**,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_normal ; 

svn_error_t *
svn_wc__read_external_info(svn_node_kind_t *external_kind,
                           const char **defining_abspath,
                           const char **defining_url,
                           svn_revnum_t *defining_operational_revision,
                           svn_revnum_t *defining_revision,
                           svn_wc_context_t *wc_ctx,
                           const char *wri_abspath,
                           const char *local_abspath,
                           svn_boolean_t ignore_enoent,
                           apr_pool_t *result_pool,
                           apr_pool_t *scratch_pool)
{
  const char *repos_root_url;
  svn_wc__db_status_t status;
  svn_node_kind_t kind;
  svn_error_t *err;

  err = svn_wc__db_external_read(&status, &kind, defining_abspath,
                                 defining_url ? &repos_root_url : NULL, NULL,
                                 defining_url, defining_operational_revision,
                                 defining_revision,
                                 wc_ctx->db, local_abspath, wri_abspath,
                                 result_pool, scratch_pool);

  if (err)
    {
      if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND || !ignore_enoent)
        return svn_error_trace(err);

      svn_error_clear(err);

      if (external_kind)
        *external_kind = svn_node_none;

      if (defining_abspath)
        *defining_abspath = NULL;

      if (defining_url)
        *defining_url = NULL;

      if (defining_operational_revision)
        *defining_operational_revision = SVN_INVALID_REVNUM;

      if (defining_revision)
        *defining_revision = SVN_INVALID_REVNUM;

      return SVN_NO_ERROR;
    }

  if (external_kind)
    {
      if (status != svn_wc__db_status_normal)
        *external_kind = svn_node_unknown;
      else
        switch(kind)
          {
            case svn_node_file:
            case svn_node_symlink:
              *external_kind = svn_node_file;
              break;
            case svn_node_dir:
              *external_kind = svn_node_dir;
              break;
            default:
              *external_kind = svn_node_none;
          }
    }

  if (defining_url && *defining_url)
    *defining_url = svn_path_url_add_component2(repos_root_url, *defining_url,
                                                result_pool);

  return SVN_NO_ERROR;
}