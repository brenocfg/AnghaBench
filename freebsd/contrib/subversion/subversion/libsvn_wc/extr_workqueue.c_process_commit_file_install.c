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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {int /*<<< orphan*/  mtime; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ apr_finfo_t ;

/* Variables and functions */
 int APR_FINFO_LINK ; 
 int APR_FINFO_MIN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  install_committed_file (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_stat (TYPE_1__*,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_global_record_fileinfo (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__internal_file_modified_p (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
process_commit_file_install(svn_wc__db_t *db,
                       const char *local_abspath,
                       svn_cancel_func_t cancel_func,
                       void *cancel_baton,
                       apr_pool_t *scratch_pool)
{
  svn_boolean_t overwrote_working;

  /* Install the new file, which may involve expanding keywords.
     A copy of this file should have been dropped into our `tmp/text-base'
     directory during the commit process.  Part of this process
     involves recording the textual timestamp for this entry.  We'd like
     to just use the timestamp of the working file, but it is possible
     that at some point during the commit, the real working file might
     have changed again.
   */

  SVN_ERR(install_committed_file(&overwrote_working, db,
                                 local_abspath,
                                 cancel_func, cancel_baton,
                                 scratch_pool));

  /* We will compute and modify the size and timestamp */
  if (overwrote_working)
    {
      apr_finfo_t finfo;

      SVN_ERR(svn_io_stat(&finfo, local_abspath,
                          APR_FINFO_MIN | APR_FINFO_LINK, scratch_pool));
      SVN_ERR(svn_wc__db_global_record_fileinfo(db, local_abspath,
                                                finfo.size, finfo.mtime,
                                                scratch_pool));
    }
  else
    {
      svn_boolean_t modified;

      /* The working copy file hasn't been overwritten.  We just
         removed the recorded size and modification time from the nodes
         record by calling svn_wc__db_global_commit().

         Now we have some file in our working copy that might be what
         we just committed, but we are not certain at this point.

         We still have a write lock here, so we check if the file is
         what we expect it to be and if it is the right file we update
         the recorded information. (If it isn't we keep the null data).

         Instead of reimplementing all this here, we just call a function
         that already does implement this when it notices that we have the
         right kind of lock (and we ignore the result)
       */
      SVN_ERR(svn_wc__internal_file_modified_p(&modified,
                                               db, local_abspath, FALSE,
                                               scratch_pool));
    }
  return SVN_NO_ERROR;
}