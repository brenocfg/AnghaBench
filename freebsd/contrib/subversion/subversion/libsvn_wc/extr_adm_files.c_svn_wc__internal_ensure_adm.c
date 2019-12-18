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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_OBSTRUCTED_UPDATE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  init_adm (int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,char const*,...) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_skip_ancestor (char const*,char const*) ; 
 char* svn_uri_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_scan_addition (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_deleted ; 
 scalar_t__ svn_wc__db_status_not_present ; 
 int /*<<< orphan*/  svn_wc__internal_check_wc (int*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__internal_ensure_adm(svn_wc__db_t *db,
                            const char *local_abspath,
                            const char *url,
                            const char *repos_root_url,
                            const char *repos_uuid,
                            svn_revnum_t revision,
                            svn_depth_t depth,
                            apr_pool_t *scratch_pool)
{
  int format;
  const char *original_repos_relpath;
  const char *original_root_url;
  svn_boolean_t is_op_root;
  const char *repos_relpath = svn_uri_skip_ancestor(repos_root_url, url,
                                                    scratch_pool);
  svn_wc__db_status_t status;
  const char *db_repos_relpath, *db_repos_root_url, *db_repos_uuid;
  svn_revnum_t db_revision;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));
  SVN_ERR_ASSERT(url != NULL);
  SVN_ERR_ASSERT(repos_root_url != NULL);
  SVN_ERR_ASSERT(repos_uuid != NULL);
  SVN_ERR_ASSERT(repos_relpath != NULL);

  SVN_ERR(svn_wc__internal_check_wc(&format, db, local_abspath, TRUE,
                                    scratch_pool));

  /* Early out: we know we're not dealing with an existing wc, so
     just create one. */
  if (format == 0)
    return svn_error_trace(init_adm(db, local_abspath,
                                    repos_relpath, repos_root_url, repos_uuid,
                                    revision, depth, scratch_pool));

  SVN_ERR(svn_wc__db_read_info(&status, NULL,
                               &db_revision, &db_repos_relpath,
                               &db_repos_root_url, &db_repos_uuid,
                               NULL, NULL, NULL, NULL, NULL, NULL,
                               &original_repos_relpath, &original_root_url,
                               NULL, NULL, NULL, NULL, NULL, NULL,
                               NULL, &is_op_root, NULL, NULL,
                               NULL, NULL, NULL,
                               db, local_abspath, scratch_pool, scratch_pool));

  /* When the directory exists and is scheduled for deletion or is not-present
   * do not check the revision or the URL.  The revision can be any
   * arbitrary revision and the URL may differ if the add is
   * being driven from a merge which will have a different URL. */
  if (status != svn_wc__db_status_deleted
      && status != svn_wc__db_status_not_present)
    {
      /* ### Should we match copyfrom_revision? */
      if (db_revision != revision)
        return
          svn_error_createf(SVN_ERR_WC_OBSTRUCTED_UPDATE, NULL,
                            _("Revision %ld doesn't match existing "
                              "revision %ld in '%s'"),
                            revision, db_revision, local_abspath);

      if (!db_repos_root_url)
        {
          if (status == svn_wc__db_status_added)
            SVN_ERR(svn_wc__db_scan_addition(NULL, NULL,
                                             &db_repos_relpath,
                                             &db_repos_root_url,
                                             &db_repos_uuid,
                                             NULL, NULL, NULL, NULL,
                                             db, local_abspath,
                                             scratch_pool, scratch_pool));
          else
            SVN_ERR(svn_wc__db_base_get_info(NULL, NULL, NULL,
                                             &db_repos_relpath,
                                             &db_repos_root_url,
                                             &db_repos_uuid, NULL, NULL, NULL,
                                             NULL, NULL, NULL, NULL, NULL,
                                             NULL, NULL,
                                             db, local_abspath,
                                             scratch_pool, scratch_pool));
        }

      /* The caller gives us a URL which should match the entry. However,
         some callers compensate for an old problem in entry->url and pass
         the copyfrom_url instead. See ^/notes/api-errata/1.7/wc002.txt. As
         a result, we allow the passed URL to match copyfrom_url if it
         does not match the entry's primary URL.  */
      if (strcmp(db_repos_uuid, repos_uuid)
          || strcmp(db_repos_root_url, repos_root_url)
          || !svn_relpath_skip_ancestor(db_repos_relpath, repos_relpath))
        {
          if (!is_op_root /* copy_from was set on op-roots only */
              || original_root_url == NULL
              || strcmp(original_root_url, repos_root_url)
              || strcmp(original_repos_relpath, repos_relpath))
            return
              svn_error_createf(SVN_ERR_WC_OBSTRUCTED_UPDATE, NULL,
                                _("URL '%s' (uuid: '%s') doesn't match existing "
                                  "URL '%s' (uuid: '%s') in '%s'"),
                                url,
                                db_repos_uuid,
                                svn_path_url_add_component2(db_repos_root_url,
                                                            db_repos_relpath,
                                                            scratch_pool),
                                repos_uuid,
                                local_abspath);
        }
    }

  return SVN_NO_ERROR;
}