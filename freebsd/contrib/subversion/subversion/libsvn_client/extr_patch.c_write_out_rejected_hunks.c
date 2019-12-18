#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_13__ {int /*<<< orphan*/  reject_stream; int /*<<< orphan*/  local_abspath; scalar_t__ had_prop_rejects; scalar_t__ had_rejects; } ;
typedef  TYPE_2__ patch_target_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_dirent_basename (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char const* svn_dirent_dirname (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 TYPE_1__* svn_io_open_uniquely_named (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stream_close (int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_stream_copy3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stream_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
write_out_rejected_hunks(patch_target_t *target,
                         const char *root_abspath,
                         svn_boolean_t dry_run,
                         apr_pool_t *scratch_pool)
{
  if (! dry_run && (target->had_rejects || target->had_prop_rejects))
    {
      /* Write out rejected hunks, if any. */
      apr_file_t *reject_file;
      svn_error_t *err;

      err = svn_io_open_uniquely_named(&reject_file, NULL,
                                       svn_dirent_dirname(target->local_abspath,
                                                          scratch_pool),
                                       svn_dirent_basename(
                                         target->local_abspath,
                                         NULL),
                                       ".svnpatch.rej",
                                       svn_io_file_del_none,
                                       scratch_pool, scratch_pool);
      if (err && APR_STATUS_IS_ENOENT(err->apr_err))
        {
          /* The hunk applies to a file in a directory which does not exist.
           * Put the reject file into the working copy root instead. */
          svn_error_clear(err);
          SVN_ERR(svn_io_open_uniquely_named(&reject_file, NULL,
                                             root_abspath,
                                             svn_dirent_basename(
                                               target->local_abspath,
                                               NULL),
                                             ".svnpatch.rej",
                                             svn_io_file_del_none,
                                             scratch_pool, scratch_pool));
        }
      else
        SVN_ERR(err);

      SVN_ERR(svn_stream_reset(target->reject_stream));

      /* svn_stream_copy3() closes the files for us */
      SVN_ERR(svn_stream_copy3(target->reject_stream,
                                  svn_stream_from_aprfile2(reject_file, FALSE,
                                                           scratch_pool),
                                  NULL, NULL, scratch_pool));
      /* ### TODO mark file as conflicted. */
    }
  else
    SVN_ERR(svn_stream_close(target->reject_stream));

  return SVN_NO_ERROR;
}