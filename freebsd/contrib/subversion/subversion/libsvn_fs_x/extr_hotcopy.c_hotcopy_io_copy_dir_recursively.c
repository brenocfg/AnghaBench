#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/ * (* svn_cancel_func_t ) (void*) ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_int32_t ;
struct TYPE_3__ {char* name; scalar_t__ filetype; } ;
typedef  TYPE_1__ apr_finfo_t ;
typedef  int /*<<< orphan*/  apr_dir_t ;

/* Variables and functions */
 scalar_t__ APR_DIR ; 
 int APR_FINFO_NAME ; 
 int APR_FINFO_TYPE ; 
 scalar_t__ APR_LNK ; 
 scalar_t__ APR_REG ; 
 int /*<<< orphan*/  APR_STATUS_IS_ENOENT (scalar_t__) ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_NODE_UNEXPECTED_KIND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_dir_close (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_dir_read (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * entry_name_to_utf8 (char const**,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hotcopy_io_dir_file_copy (int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 char* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_copy_link (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_dir_open (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_make_dir_recursively (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
hotcopy_io_copy_dir_recursively(svn_boolean_t *skipped_p,
                                const char *src,
                                const char *dst_parent,
                                const char *dst_basename,
                                svn_boolean_t copy_perms,
                                svn_cancel_func_t cancel_func,
                                void *cancel_baton,
                                apr_pool_t *scratch_pool)
{
  svn_node_kind_t kind;
  apr_status_t status;
  const char *dst_path;
  apr_dir_t *this_dir;
  apr_finfo_t this_entry;
  apr_int32_t flags = APR_FINFO_TYPE | APR_FINFO_NAME;

  /* Make a subpool for recursion */
  apr_pool_t *subpool = svn_pool_create(scratch_pool);

  /* The 'dst_path' is simply dst_parent/dst_basename */
  dst_path = svn_dirent_join(dst_parent, dst_basename, scratch_pool);

  /* Sanity checks:  SRC and DST_PARENT are directories, and
     DST_BASENAME doesn't already exist in DST_PARENT. */
  SVN_ERR(svn_io_check_path(src, &kind, subpool));
  if (kind != svn_node_dir)
    return svn_error_createf(SVN_ERR_NODE_UNEXPECTED_KIND, NULL,
                             _("Source '%s' is not a directory"),
                             svn_dirent_local_style(src, scratch_pool));

  SVN_ERR(svn_io_check_path(dst_parent, &kind, subpool));
  if (kind != svn_node_dir)
    return svn_error_createf(SVN_ERR_NODE_UNEXPECTED_KIND, NULL,
                             _("Destination '%s' is not a directory"),
                             svn_dirent_local_style(dst_parent,
                                                    scratch_pool));

  SVN_ERR(svn_io_check_path(dst_path, &kind, subpool));

  /* Create the new directory. */
  /* ### TODO: copy permissions (needs apr_file_attrs_get()) */
  SVN_ERR(svn_io_make_dir_recursively(dst_path, scratch_pool));

  /* Loop over the dirents in SRC.  ('.' and '..' are auto-excluded) */
  SVN_ERR(svn_io_dir_open(&this_dir, src, subpool));

  for (status = apr_dir_read(&this_entry, flags, this_dir);
       status == APR_SUCCESS;
       status = apr_dir_read(&this_entry, flags, this_dir))
    {
      if ((this_entry.name[0] == '.')
          && ((this_entry.name[1] == '\0')
              || ((this_entry.name[1] == '.')
                  && (this_entry.name[2] == '\0'))))
        {
          continue;
        }
      else
        {
          const char *entryname_utf8;

          if (cancel_func)
            SVN_ERR(cancel_func(cancel_baton));

          SVN_ERR(entry_name_to_utf8(&entryname_utf8, this_entry.name,
                                     src, subpool));
          if (this_entry.filetype == APR_REG) /* regular file */
            {
              SVN_ERR(hotcopy_io_dir_file_copy(skipped_p, src, dst_path,
                                               entryname_utf8, subpool));
            }
          else if (this_entry.filetype == APR_LNK) /* symlink */
            {
              const char *src_target = svn_dirent_join(src, entryname_utf8,
                                                       subpool);
              const char *dst_target = svn_dirent_join(dst_path,
                                                       entryname_utf8,
                                                       subpool);
              SVN_ERR(svn_io_copy_link(src_target, dst_target,
                                       subpool));
            }
          else if (this_entry.filetype == APR_DIR) /* recurse */
            {
              const char *src_target;

              /* Prevent infinite recursion by filtering off our
                 newly created destination path. */
              if (strcmp(src, dst_parent) == 0
                  && strcmp(entryname_utf8, dst_basename) == 0)
                continue;

              src_target = svn_dirent_join(src, entryname_utf8, subpool);
              SVN_ERR(hotcopy_io_copy_dir_recursively(skipped_p,
                                                      src_target,
                                                      dst_path,
                                                      entryname_utf8,
                                                      copy_perms,
                                                      cancel_func,
                                                      cancel_baton,
                                                      subpool));
            }
          /* ### support other APR node types someday?? */

        }
    }

  if (! (APR_STATUS_IS_ENOENT(status)))
    return svn_error_wrap_apr(status, _("Can't read directory '%s'"),
                              svn_dirent_local_style(src, scratch_pool));

  status = apr_dir_close(this_dir);
  if (status)
    return svn_error_wrap_apr(status, _("Error closing directory '%s'"),
                              svn_dirent_local_style(src, scratch_pool));

  /* Free any memory used by recursion */
  svn_pool_destroy(subpool);

  return SVN_NO_ERROR;
}