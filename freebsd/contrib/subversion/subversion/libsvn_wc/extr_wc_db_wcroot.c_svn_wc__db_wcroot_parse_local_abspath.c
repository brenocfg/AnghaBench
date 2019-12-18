#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_wcroot_t ;
struct TYPE_33__ {int /*<<< orphan*/  state_pool; int /*<<< orphan*/  dir_data; int /*<<< orphan*/  verify_format; int /*<<< orphan*/  timeout; int /*<<< orphan*/  exclusive; } ;
typedef  TYPE_1__ svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_34__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
struct TYPE_35__ {int size; } ;
typedef  TYPE_3__ apr_finfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FINFO_SIZE ; 
 scalar_t__ APR_STATUS_IS_ENOENT (scalar_t__) ; 
 int FALSE ; 
 int /*<<< orphan*/  SDB_FILE ; 
 int /*<<< orphan*/  STMT_VERIFICATION_TRIGGERS ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 scalar_t__ SVN_ERR_SQLITE_ERROR ; 
 scalar_t__ SVN_ERR_WC_CORRUPT ; 
 scalar_t__ SVN_ERR_WC_NOT_WORKING_COPY ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 scalar_t__ SVN_ERR_WC_UNSUPPORTED_FORMAT ; 
 scalar_t__ SVN_ERR_WC_UPGRADE_REQUIRED ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__ADM_ENTRIES ; 
 int /*<<< orphan*/  SVN_WC__ERR_IS_NOT_CURRENT_WC (TYPE_2__*) ; 
 int SVN_WC__WC_NG_VERSION ; 
 int TRUE ; 
 int /*<<< orphan*/  UNKNOWN_WC_ID ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 char* compute_relpath (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* fetch_sdb_info (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* get_old_version (int*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* get_path_kind (scalar_t__*,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* read_link_target (char const**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_dirent_is_root (char const*,int /*<<< orphan*/ ) ; 
 char* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_compose_create (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* svn_error_createf (scalar_t__,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_quick_wrapf (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_check_resolved_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_stat (TYPE_3__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_none ; 
 scalar_t__ svn_node_symlink ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_sqlite__close (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_sqlite__exec_statements (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__mode_readwrite ; 
 char* svn_wc__adm_child (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_pdh_create_wcroot (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_read_info_internal (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_not_present ; 
 scalar_t__ svn_wc__db_status_server_excluded ; 
 TYPE_2__* svn_wc__db_util_open_db (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_wc_get_adm_dir (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_wcroot_parse_local_abspath(svn_wc__db_wcroot_t **wcroot,
                                      const char **local_relpath,
                                      svn_wc__db_t *db,
                                      const char *local_abspath,
                                      apr_pool_t *result_pool,
                                      apr_pool_t *scratch_pool)
{
  const char *local_dir_abspath;
  const char *original_abspath = local_abspath;
  svn_node_kind_t kind;
  const char *build_relpath;
  svn_wc__db_wcroot_t *probe_wcroot;
  svn_wc__db_wcroot_t *found_wcroot = NULL;
  const char *scan_abspath;
  svn_sqlite__db_t *sdb = NULL;
  svn_boolean_t moved_upwards = FALSE;
  svn_boolean_t always_check = FALSE;
  int wc_format = 0;
  const char *adm_relpath;
  /* Non-NULL if WCROOT is found through a symlink: */
  const char *symlink_wcroot_abspath = NULL;

  /* ### we need more logic for finding the database (if it is located
     ### outside of the wcroot) and then managing all of that within DB.
     ### for now: play quick & dirty. */

  probe_wcroot = svn_hash_gets(db->dir_data, local_abspath);
  if (probe_wcroot != NULL)
    {
      *wcroot = probe_wcroot;

      /* We got lucky. Just return the thing BEFORE performing any I/O.  */
      /* ### validate SMODE against how we opened wcroot->sdb? and against
         ### DB->mode? (will we record per-dir mode?)  */

      /* ### for most callers, we could pass NULL for result_pool.  */
      *local_relpath = compute_relpath(probe_wcroot, local_abspath,
                                       result_pool);

      return SVN_NO_ERROR;
    }

  /* ### at some point in the future, we may need to find a way to get
     ### rid of this stat() call. it is going to happen for EVERY call
     ### into wc_db which references a file. calls for directories could
     ### get an early-exit in the hash lookup just above.  */
  SVN_ERR(get_path_kind(&kind, db, local_abspath, scratch_pool));
  if (kind != svn_node_dir)
    {
      /* If the node specified by the path is NOT present, then it cannot
         possibly be a directory containing ".svn/wc.db".

         If it is a file, then it cannot contain ".svn/wc.db".

         For both of these cases, strip the basename off of the path and
         move up one level. Keep record of what we strip, though, since
         we'll need it later to construct local_relpath.  */
      svn_dirent_split(&local_dir_abspath, &build_relpath, local_abspath,
                       scratch_pool);

      /* Is this directory in our hash?  */
      probe_wcroot = svn_hash_gets(db->dir_data, local_dir_abspath);
      if (probe_wcroot != NULL)
        {
          const char *dir_relpath;

          *wcroot = probe_wcroot;

          /* Stashed directory's local_relpath + basename. */
          dir_relpath = compute_relpath(probe_wcroot, local_dir_abspath,
                                        NULL);
          *local_relpath = svn_relpath_join(dir_relpath,
                                            build_relpath,
                                            result_pool);
          return SVN_NO_ERROR;
        }

      /* If the requested path is not on the disk, then we don't know how
         many ancestors need to be scanned until we start hitting content
         on the disk. Set ALWAYS_CHECK to keep looking for .svn/entries
         rather than bailing out after the first check.  */
      if (kind == svn_node_none)
        always_check = TRUE;

      /* Start the scanning at LOCAL_DIR_ABSPATH.  */
      local_abspath = local_dir_abspath;
    }
  else
    {
      /* Start the local_relpath empty. If *this* directory contains the
         wc.db, then relpath will be the empty string.  */
      build_relpath = "";

      /* Remember the dir containing LOCAL_ABSPATH (they're the same).  */
      local_dir_abspath = local_abspath;
    }

  /* LOCAL_ABSPATH refers to a directory at this point. At this point,
     we've determined that an associated WCROOT is NOT in the DB's hash
     table for this directory. Let's find an existing one in the ancestors,
     or create one when we find the actual wcroot.  */

  /* Assume that LOCAL_ABSPATH is a directory, and look for the SQLite
     database in the right place. If we find it... great! If not, then
     peel off some components, and try again. */

  adm_relpath = svn_wc_get_adm_dir(scratch_pool);
  while (TRUE)
    {
      svn_error_t *err;
      svn_node_kind_t adm_subdir_kind;

      const char *adm_subdir = svn_dirent_join(local_abspath, adm_relpath,
                                               scratch_pool);

      SVN_ERR(svn_io_check_path(adm_subdir, &adm_subdir_kind, scratch_pool));

      if (adm_subdir_kind == svn_node_dir)
        {
          /* We always open the database in read/write mode.  If the database
             isn't writable in the filesystem, SQLite will internally open
             it as read-only, and we'll get an error if we try to do a write
             operation.

             We could decide what to do on a per-operation basis, but since
             we're caching database handles, it make sense to be as permissive
             as the filesystem allows. */
          err = svn_wc__db_util_open_db(&sdb, local_abspath, SDB_FILE,
                                        svn_sqlite__mode_readwrite,
                                        db->exclusive, db->timeout, NULL,
                                        db->state_pool, scratch_pool);
          if (err == NULL)
            {
#ifdef SVN_DEBUG
              /* Install self-verification trigger statements. */
              err = svn_sqlite__exec_statements(sdb,
                                                STMT_VERIFICATION_TRIGGERS);
              if (err && err->apr_err == SVN_ERR_SQLITE_ERROR)
                {
                  /* Verification triggers can fail to install on old 1.7-dev
                   * formats which didn't have a NODES table yet. Ignore sqlite
                   * errors so such working copies can be upgraded. */
                  svn_error_clear(err);
                }
              else
                SVN_ERR(err);
#endif
              break;
            }
          if (err->apr_err != SVN_ERR_SQLITE_ERROR
              && !APR_STATUS_IS_ENOENT(err->apr_err))
            return svn_error_trace(err);
          svn_error_clear(err);

          /* If we have not moved upwards, then check for a wc-1 working copy.
             Since wc-1 has a .svn in every directory, and we didn't find one
             in the original directory, then we aren't looking at a wc-1.

             If the original path is not present, then we have to check on every
             iteration. The content may be the immediate parent, or possibly
             five ancetors higher. We don't test for directory presence (just
             for the presence of subdirs/files), so we don't know when we can
             stop checking ... so just check always.  */
          if (!moved_upwards || always_check)
            {
              SVN_ERR(get_old_version(&wc_format, local_abspath,
                                      scratch_pool));
              if (wc_format != 0)
                break;
            }
        }

      /* We couldn't open the SDB within the specified directory, so
         move up one more directory. */
      if (svn_dirent_is_root(local_abspath, strlen(local_abspath)))
        {
          /* Hit the root without finding a wcroot. */

          /* The wcroot could be a symlink to a directory.
           * (Issue #2557, #3987). If so, try again, this time scanning
           * for a db within the directory the symlink points to,
           * rather than within the symlink's parent directory. */
          if (kind == svn_node_symlink)
            {
              svn_node_kind_t resolved_kind;

              local_abspath = original_abspath;

              SVN_ERR(svn_io_check_resolved_path(local_abspath,
                                                 &resolved_kind,
                                                 scratch_pool));
              if (resolved_kind == svn_node_dir)
                {
                  /* Is this directory recorded in our hash?  */
                  found_wcroot = svn_hash_gets(db->dir_data, local_abspath);
                  if (found_wcroot)
                    break;

                  symlink_wcroot_abspath = local_abspath;
                  SVN_ERR(read_link_target(&local_abspath, local_abspath,
                                           scratch_pool));
try_symlink_as_dir:
                  kind = svn_node_dir;
                  moved_upwards = FALSE;
                  local_dir_abspath = local_abspath;
                  build_relpath = "";

                  continue;
                }
            }

          return svn_error_createf(SVN_ERR_WC_NOT_WORKING_COPY, NULL,
                                   _("'%s' is not a working copy"),
                                   svn_dirent_local_style(original_abspath,
                                                          scratch_pool));
        }

      local_abspath = svn_dirent_dirname(local_abspath, scratch_pool);

      moved_upwards = TRUE;
      symlink_wcroot_abspath = NULL;

      /* Is the parent directory recorded in our hash?  */
      found_wcroot = svn_hash_gets(db->dir_data, local_abspath);
      if (found_wcroot != NULL)
        break;
    }

  if (found_wcroot != NULL)
    {
      /* We found a hash table entry for an ancestor, so we stopped scanning
         since all subdirectories use the same WCROOT.  */
      *wcroot = found_wcroot;
    }
  else if (wc_format == 0)
    {
      /* We finally found the database. Construct a wcroot_t for it.  */

      apr_int64_t wc_id;
      int format;
      svn_error_t *err;

      err = fetch_sdb_info(&wc_id, &format, sdb, scratch_pool);
      if (err)
        {
          if (err->apr_err == SVN_ERR_WC_CORRUPT)
            return svn_error_quick_wrapf(
              err, _("Missing a row in WCROOT for '%s'."),
              svn_dirent_local_style(original_abspath, scratch_pool));
          return svn_error_trace(err);
        }

      /* WCROOT.local_abspath may be NULL when the database is stored
         inside the wcroot, but we know the abspath is this directory
         (ie. where we found it).  */

      err = svn_wc__db_pdh_create_wcroot(wcroot,
                            apr_pstrdup(db->state_pool,
                                        symlink_wcroot_abspath
                                          ? symlink_wcroot_abspath
                                          : local_abspath),
                            sdb, wc_id, format,
                            db->verify_format,
                            db->state_pool, scratch_pool);
      if (err && (err->apr_err == SVN_ERR_WC_UNSUPPORTED_FORMAT ||
                  err->apr_err == SVN_ERR_WC_UPGRADE_REQUIRED) &&
          kind == svn_node_symlink)
        {
          /* We found an unsupported WC after traversing upwards from a
           * symlink. Fall through to code below to check if the symlink
           * points at a supported WC. */
          svn_error_clear(err);
          *wcroot = NULL;
        }
      else if (err)
        {
          /* Close handle if we are not going to use it to support
             upgrading with exclusive wc locking. */
          return svn_error_compose_create(err, svn_sqlite__close(sdb));
        }
    }
  else
    {
      /* We found something that looks like a wc-1 working copy directory.
         However, if the format version is 12 and the .svn/entries file
         is only 3 bytes long, then it's a breadcrumb in a wc-ng working
         copy that's missing an .svn/wc.db, or its .svn/wc.db is corrupt. */
      if (wc_format == SVN_WC__WC_NG_VERSION /* 12 */)
        {
          apr_finfo_t info;

          /* Check attributes of .svn/entries */
          const char *admin_abspath = svn_wc__adm_child(
              local_abspath, SVN_WC__ADM_ENTRIES, scratch_pool);
          svn_error_t *err = svn_io_stat(&info, admin_abspath, APR_FINFO_SIZE,
                                         scratch_pool);

          /* If the former does not succeed, something is seriously wrong. */
          if (err)
            return svn_error_createf(
                SVN_ERR_WC_CORRUPT, err,
                _("The working copy at '%s' is corrupt."),
                svn_dirent_local_style(local_abspath, scratch_pool));
          svn_error_clear(err);

          if (3 == info.size)
            {
              /* Check existence of .svn/wc.db */
              admin_abspath = svn_wc__adm_child(local_abspath, SDB_FILE,
                                                scratch_pool);
              err = svn_io_stat(&info, admin_abspath, APR_FINFO_SIZE,
                                scratch_pool);
              if (err && APR_STATUS_IS_ENOENT(err->apr_err))
                {
                  svn_error_clear(err);
                  return svn_error_createf(
                      SVN_ERR_WC_CORRUPT, NULL,
                      _("The working copy database at '%s' is missing."),
                      svn_dirent_local_style(local_abspath, scratch_pool));
                }
              else
                /* We should never have reached this point in the code
                   if .svn/wc.db exists; therefore it's best to assume
                   it's corrupt. */
                return svn_error_createf(
                    SVN_ERR_WC_CORRUPT, err,
                    _("The working copy database at '%s' is corrupt."),
                    svn_dirent_local_style(local_abspath, scratch_pool));
            }
        }

      SVN_ERR(svn_wc__db_pdh_create_wcroot(wcroot,
                            apr_pstrdup(db->state_pool,
                                        symlink_wcroot_abspath
                                          ? symlink_wcroot_abspath
                                          : local_abspath),
                            NULL, UNKNOWN_WC_ID, wc_format,
                            db->verify_format,
                            db->state_pool, scratch_pool));
    }

  if (*wcroot)
    {
      const char *dir_relpath;

      if (symlink_wcroot_abspath)
        {
          /* The WCROOT was found through a symlink pointing at the root of
           * the WC. Cache the WCROOT under the symlink's path. */
          local_dir_abspath = symlink_wcroot_abspath;
        }

      /* The subdirectory's relpath is easily computed relative to the
         wcroot that we just found.  */
      dir_relpath = compute_relpath(*wcroot, local_dir_abspath, NULL);

      /* And the result local_relpath may include a filename.  */
      *local_relpath = svn_relpath_join(dir_relpath, build_relpath, result_pool);
    }

  if (kind == svn_node_symlink)
    {
      svn_boolean_t retry_if_dir = FALSE;
      svn_wc__db_status_t status;
      svn_boolean_t conflicted;
      svn_error_t *err;

      /* Check if the symlink is versioned or obstructs a versioned node
       * in this DB -- in that case, use this wcroot. Else, if the symlink
       * points to a directory, try to find a wcroot in that directory
       * instead. */

      if (*wcroot)
        {
          err = svn_wc__db_read_info_internal(&status, NULL, NULL, NULL, NULL,
                                              NULL, NULL, NULL, NULL, NULL,
                                              NULL, NULL, NULL, NULL, NULL,
                                              NULL, NULL, NULL, &conflicted,
                                              NULL, NULL, NULL, NULL, NULL,
                                              NULL, *wcroot, *local_relpath,
                                              scratch_pool, scratch_pool);
          if (err)
            {
              if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND
                  && !SVN_WC__ERR_IS_NOT_CURRENT_WC(err))
                return svn_error_trace(err);

              svn_error_clear(err);
              retry_if_dir = TRUE; /* The symlink is unversioned. */
            }
          else
            {
              /* The symlink is versioned, or obstructs a versioned node.
               * Ignore non-conflicted not-present/excluded nodes.
               * This allows the symlink to redirect the wcroot query to a
               * directory, regardless of 'invisible' nodes in this WC. */
              retry_if_dir = ((status == svn_wc__db_status_not_present ||
                               status == svn_wc__db_status_excluded ||
                               status == svn_wc__db_status_server_excluded)
                              && !conflicted);
            }
        }
      else
        retry_if_dir = TRUE;

      if (retry_if_dir)
        {
          svn_node_kind_t resolved_kind;

          SVN_ERR(svn_io_check_resolved_path(original_abspath,
                                             &resolved_kind,
                                             scratch_pool));
          if (resolved_kind == svn_node_dir)
            {
              symlink_wcroot_abspath = original_abspath;
              SVN_ERR(read_link_target(&local_abspath, original_abspath,
                                       scratch_pool));
              /* This handle was opened in this function but is not going
                 to be used further so close it. */
              if (sdb)
                SVN_ERR(svn_sqlite__close(sdb));
              goto try_symlink_as_dir;
            }
        }
    }

  /* We've found the appropriate WCROOT for the requested path. Stash
     it into that path's directory.  */
  svn_hash_sets(db->dir_data,
                apr_pstrdup(db->state_pool, local_dir_abspath),
                *wcroot);

  /* Did we traverse up to parent directories?  */
  if (!moved_upwards)
    {
      /* We did NOT move to a parent of the original requested directory.
         We've constructed and filled in a WCROOT for the request, so we
         are done.  */
      return SVN_NO_ERROR;
    }

  /* The WCROOT that we just found/built was for the LOCAL_ABSPATH originally
     passed into this function. We stepped *at least* one directory above that.
     We should now associate the WROOT for each parent directory that does
     not (yet) have one.  */

  scan_abspath = local_dir_abspath;

  do
    {
      const char *parent_dir = svn_dirent_dirname(scan_abspath, scratch_pool);
      svn_wc__db_wcroot_t *parent_wcroot;

      parent_wcroot = svn_hash_gets(db->dir_data, parent_dir);
      if (parent_wcroot == NULL)
        {
          svn_hash_sets(db->dir_data, apr_pstrdup(db->state_pool, parent_dir),
                        *wcroot);
        }

      /* Move up a directory, stopping when we reach the directory where
         we found/built the WCROOT.  */
      scan_abspath = parent_dir;
    }
  while (strcmp(scan_abspath, local_abspath) != 0);

  return SVN_NO_ERROR;
}