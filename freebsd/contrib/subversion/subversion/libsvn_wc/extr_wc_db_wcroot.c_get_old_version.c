#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_8__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_STATUS_IS_ENOENT (scalar_t__) ; 
 int /*<<< orphan*/  APR_STATUS_IS_ENOTDIR (scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_BAD_VERSION_FILE_FORMAT ; 
 int /*<<< orphan*/  SVN_ERR_WC_MISSING ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__ADM_ENTRIES ; 
 int /*<<< orphan*/  SVN_WC__ADM_FORMAT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_createf (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_io_read_version_file (int*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 char* svn_wc__adm_child (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_old_version(int *version,
                const char *abspath,
                apr_pool_t *scratch_pool)
{
  svn_error_t *err;
  const char *format_file_path;
  svn_node_kind_t kind;

  /* Try reading the format number from the entries file.  */
  format_file_path = svn_wc__adm_child(abspath, SVN_WC__ADM_ENTRIES,
                                       scratch_pool);

  /* Since trying to open a non-existent file is quite expensive, try a
     quick stat call first. In wc-ng w/cs, this will be an early exit. */
  SVN_ERR(svn_io_check_path(format_file_path, &kind, scratch_pool));
  if (kind == svn_node_none)
    {
      *version = 0;
      return SVN_NO_ERROR;
    }

  err = svn_io_read_version_file(version, format_file_path, scratch_pool);
  if (err == NULL)
    return SVN_NO_ERROR;
  if (err->apr_err != SVN_ERR_BAD_VERSION_FILE_FORMAT
      && !APR_STATUS_IS_ENOENT(err->apr_err)
      && !APR_STATUS_IS_ENOTDIR(err->apr_err))
    return svn_error_createf(SVN_ERR_WC_MISSING, err, _("'%s' does not exist"),
                             svn_dirent_local_style(abspath, scratch_pool));
  svn_error_clear(err);

  /* This must be a really old working copy!  Fall back to reading the
     format file.

     Note that the format file might not exist in newer working copies
     (format 7 and higher), but in that case, the entries file should
     have contained the format number. */
  format_file_path = svn_wc__adm_child(abspath, SVN_WC__ADM_FORMAT,
                                       scratch_pool);
  err = svn_io_read_version_file(version, format_file_path, scratch_pool);
  if (err == NULL)
    return SVN_NO_ERROR;

  /* Whatever error may have occurred... we can just ignore. This is not
     a working copy directory. Signal the caller.  */
  svn_error_clear(err);

  *version = 0;
  return SVN_NO_ERROR;
}