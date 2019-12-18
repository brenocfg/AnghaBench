#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  (* svn_wc_notify_func2_t ) (void*,TYPE_1__*,int /*<<< orphan*/ *) ;
struct TYPE_11__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_3__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_from_disk (int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_can_add_node (scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_can_add_to_parent (char const**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  integrate_nested_wc_as_copy (TYPE_3__*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  stub1 (void*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,...) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_uri__is_ancestor (char const*,char const*) ; 
 char* svn_uri_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_copy_dir (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wclock_obtain (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wclock_owns_lock (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_add_repos_file4 (TYPE_3__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_add ; 

svn_error_t *
svn_wc_add4(svn_wc_context_t *wc_ctx,
            const char *local_abspath,
            svn_depth_t depth,
            const char *copyfrom_url,
            svn_revnum_t copyfrom_rev,
            svn_cancel_func_t cancel_func,
            void *cancel_baton,
            svn_wc_notify_func2_t notify_func,
            void *notify_baton,
            apr_pool_t *scratch_pool)
{
  svn_wc__db_t *db = wc_ctx->db;
  svn_node_kind_t kind;
  svn_boolean_t db_row_exists;
  svn_boolean_t is_wc_root;
  const char *repos_root_url;
  const char *repos_uuid;

  SVN_ERR(check_can_add_node(&kind, &db_row_exists, &is_wc_root,
                             db, local_abspath, copyfrom_url, copyfrom_rev,
                             scratch_pool));

  /* Get REPOS_ROOT_URL and REPOS_UUID.  Check that the
     parent is a versioned directory in an acceptable state. */
  SVN_ERR(check_can_add_to_parent(&repos_root_url, &repos_uuid,
                                  db, local_abspath, scratch_pool,
                                  scratch_pool));

  /* If we're performing a repos-to-WC copy, check that the copyfrom
     repository is the same as the parent dir's repository. */
  if (copyfrom_url && !svn_uri__is_ancestor(repos_root_url, copyfrom_url))
    return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                             _("The URL '%s' has a different repository "
                               "root than its parent"), copyfrom_url);

  /* Verify that we can actually integrate the inner working copy */
  if (is_wc_root)
    {
      const char *repos_relpath, *inner_repos_root_url, *inner_repos_uuid;
      const char *inner_url;

      SVN_ERR(svn_wc__db_base_get_info(NULL, NULL, NULL, &repos_relpath,
                                       &inner_repos_root_url,
                                       &inner_repos_uuid, NULL, NULL, NULL,
                                       NULL, NULL, NULL, NULL, NULL, NULL,
                                       NULL,
                                       db, local_abspath,
                                       scratch_pool, scratch_pool));

      if (strcmp(inner_repos_uuid, repos_uuid)
          || strcmp(repos_root_url, inner_repos_root_url))
        return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                                 _("Can't schedule the working copy at '%s' "
                                   "from repository '%s' with uuid '%s' "
                                   "for addition under a working copy from "
                                   "repository '%s' with uuid '%s'."),
                                 svn_dirent_local_style(local_abspath,
                                                        scratch_pool),
                                 inner_repos_root_url, inner_repos_uuid,
                                 repos_root_url, repos_uuid);

      inner_url = svn_path_url_add_component2(repos_root_url, repos_relpath,
                                              scratch_pool);

      if (strcmp(copyfrom_url, inner_url))
        return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                                 _("Can't add '%s' with URL '%s', but with "
                                   "the data from '%s'"),
                                 svn_dirent_local_style(local_abspath,
                                                        scratch_pool),
                                 copyfrom_url, inner_url);
    }

  if (!copyfrom_url)  /* Case 2a: It's a simple add */
    {
      SVN_ERR(add_from_disk(db, local_abspath, kind, NULL,
                            scratch_pool));
      if (kind == svn_node_dir && !db_row_exists)
        {
          /* If using the legacy 1.6 interface the parent lock may not
             be recursive and add is expected to lock the new dir.

             ### Perhaps the lock should be created in the same
             transaction that adds the node? */
          svn_boolean_t owns_lock;

          SVN_ERR(svn_wc__db_wclock_owns_lock(&owns_lock, db, local_abspath,
                                              FALSE, scratch_pool));
          if (!owns_lock)
            SVN_ERR(svn_wc__db_wclock_obtain(db, local_abspath, 0, FALSE,
                                             scratch_pool));
        }
    }
  else if (!is_wc_root)  /* Case 2b: It's a copy from the repository */
    {
      if (kind == svn_node_file)
        {
          /* This code should never be used, as it doesn't install proper
             pristine and/or properties. But it was not an error in the old
             version of this function.

             ===> Use svn_wc_add_repos_file4() directly! */
          svn_stream_t *content = svn_stream_empty(scratch_pool);

          SVN_ERR(svn_wc_add_repos_file4(wc_ctx, local_abspath,
                                         content, NULL, NULL, NULL,
                                         copyfrom_url, copyfrom_rev,
                                         cancel_func, cancel_baton,
                                         scratch_pool));
        }
      else
        {
          const char *repos_relpath =
            svn_uri_skip_ancestor(repos_root_url, copyfrom_url, scratch_pool);

          SVN_ERR(svn_wc__db_op_copy_dir(db, local_abspath,
                                         apr_hash_make(scratch_pool),
                                         copyfrom_rev, 0, NULL,
                                         repos_relpath,
                                         repos_root_url, repos_uuid,
                                         copyfrom_rev,
                                         NULL /* children */, depth,
                                         FALSE /* is_move */,
                                         NULL /* conflicts */,
                                         NULL /* work items */,
                                         scratch_pool));
        }
    }
  else  /* Case 1: Integrating a separate WC into this one, in place */
    {
      SVN_ERR(integrate_nested_wc_as_copy(wc_ctx, local_abspath,
                                          scratch_pool));
    }

  /* Report the addition to the caller. */
  if (notify_func != NULL)
    {
      svn_wc_notify_t *notify = svn_wc_create_notify(local_abspath,
                                                     svn_wc_notify_add,
                                                     scratch_pool);
      notify->kind = kind;
      (*notify_func)(notify_baton, notify, scratch_pool);
    }

  return SVN_NO_ERROR;
}