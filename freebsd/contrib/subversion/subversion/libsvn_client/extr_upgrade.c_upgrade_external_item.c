#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  number; } ;
struct TYPE_27__ {scalar_t__ kind; TYPE_3__ value; } ;
struct TYPE_24__ {int /*<<< orphan*/  number; } ;
struct TYPE_25__ {scalar_t__ kind; TYPE_1__ value; } ;
struct TYPE_28__ {TYPE_4__ revision; TYPE_2__ peg_revision; int /*<<< orphan*/  target_dir; } ;
typedef  TYPE_5__ svn_wc_external_item2_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
struct TYPE_29__ {scalar_t__ apr_err; } ;
typedef  TYPE_6__ svn_error_t ;
struct TYPE_30__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_7__ svn_client_ctx_t ;
struct repos_info_baton {int dummy; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_6__*) ; 
 scalar_t__ SVN_ERR_WC_UPGRADE_REQUIRED ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_6__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_6__* fetch_repos_info (char const**,char const**,struct repos_info_baton*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 TYPE_6__* svn_client_upgrade (char const*,TYPE_7__*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_6__*) ; 
 TYPE_6__* svn_error_trace (TYPE_6__*) ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 scalar_t__ svn_opt_revision_number ; 
 int /*<<< orphan*/  svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_uri_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_6__* svn_wc__node_get_repos_info (int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_6__* svn_wc__resolve_relative_external_url (char const**,TYPE_5__*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_6__* svn_wc__upgrade_add_external_info (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__* svn_wc_read_kind2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
upgrade_external_item(svn_client_ctx_t *ctx,
                      const char *externals_parent_abspath,
                      const char *externals_parent_url,
                      const char *externals_parent_repos_root_url,
                      svn_wc_external_item2_t *item,
                      struct repos_info_baton *info_baton,
                      apr_pool_t *scratch_pool)
{
  const char *resolved_url;
  const char *external_abspath;
  const char *repos_relpath;
  const char *repos_root_url;
  const char *repos_uuid;
  svn_node_kind_t external_kind;
  svn_revnum_t peg_revision;
  svn_revnum_t revision;
  svn_error_t *err;

  external_abspath = svn_dirent_join(externals_parent_abspath,
                                     item->target_dir,
                                     scratch_pool);

  SVN_ERR(svn_wc__resolve_relative_external_url(
              &resolved_url,
              item,
              externals_parent_repos_root_url,
              externals_parent_url,
              scratch_pool, scratch_pool));

  /* This is a hack. We only need to call svn_wc_upgrade() on external
   * dirs, as file externals are upgraded along with their defining
   * WC.  Reading the kind will throw an exception on an external dir,
   * saying that the wc must be upgraded.  If it's a file, the lookup
   * is done in an adm_dir belonging to the defining wc (which has
   * already been upgraded) and no error is returned.  If it doesn't
   * exist (external that isn't checked out yet), we'll just get
   * svn_node_none. */
  err = svn_wc_read_kind2(&external_kind, ctx->wc_ctx,
                          external_abspath, TRUE, FALSE, scratch_pool);
  if (err && err->apr_err == SVN_ERR_WC_UPGRADE_REQUIRED)
    {
      svn_error_clear(err);

      SVN_ERR(svn_client_upgrade(external_abspath, ctx, scratch_pool));
    }
  else if (err)
    return svn_error_trace(err);

  /* The upgrade of any dir should be done now, get the now reliable
   * kind. */
  SVN_ERR(svn_wc_read_kind2(&external_kind, ctx->wc_ctx, external_abspath,
                            TRUE, FALSE, scratch_pool));

  /* Update the EXTERNALS table according to the root URL,
   * relpath and uuid known in the upgraded external WC. */

  /* We should probably have a function that provides all three
   * of root URL, repos relpath and uuid at once, but here goes... */

  /* First get the relpath, as that returns SVN_ERR_WC_PATH_NOT_FOUND
   * when the node is not present in the file system.
   * svn_wc__node_get_repos_info() would try to derive the URL. */
  SVN_ERR(svn_wc__node_get_repos_info(NULL,
                                      &repos_relpath,
                                      &repos_root_url,
                                      &repos_uuid,
                                      ctx->wc_ctx,
                                      external_abspath,
                                      scratch_pool, scratch_pool));

  /* If we haven't got any information from the checked out external,
   * or if the URL information mismatches the external's definition,
   * ask fetch_repos_info() to find out the repos root. */
  if (0 != strcmp(resolved_url,
                  svn_path_url_add_component2(repos_root_url,
                                              repos_relpath,
                                              scratch_pool)))
    {
      SVN_ERR(fetch_repos_info(&repos_root_url, &repos_uuid, info_baton,
                               resolved_url, scratch_pool, scratch_pool));

      repos_relpath = svn_uri_skip_ancestor(repos_root_url,
                                            resolved_url,
                                            scratch_pool);

      /* There's just the URL, no idea what kind the external is.
       * That's fine, as the external isn't even checked out yet.
       * The kind will be set during the next 'update'. */
      external_kind = svn_node_unknown;
    }

  peg_revision = (item->peg_revision.kind == svn_opt_revision_number
                     ? item->peg_revision.value.number
                     : SVN_INVALID_REVNUM);

  revision = (item->revision.kind == svn_opt_revision_number
                 ? item->revision.value.number
                 : SVN_INVALID_REVNUM);

  SVN_ERR(svn_wc__upgrade_add_external_info(ctx->wc_ctx,
                                            external_abspath,
                                            external_kind,
                                            externals_parent_abspath,
                                            repos_relpath,
                                            repos_root_url,
                                            repos_uuid,
                                            peg_revision,
                                            revision,
                                            scratch_pool));

  return SVN_NO_ERROR;
}