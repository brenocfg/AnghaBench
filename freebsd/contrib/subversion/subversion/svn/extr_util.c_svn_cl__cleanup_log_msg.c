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
struct TYPE_8__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct log_msg_baton {int /*<<< orphan*/  tmpfile_left; int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_compose (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_create (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_io_remove_file2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_cl__cleanup_log_msg(void *log_msg_baton,
                        svn_error_t *commit_err,
                        apr_pool_t *pool)
{
  struct log_msg_baton *lmb = log_msg_baton;
  svn_error_t *err;

  /* If there was no tmpfile left, or there is no log message baton,
     return COMMIT_ERR. */
  if ((! lmb) || (! lmb->tmpfile_left))
    return commit_err;

  /* If there was no commit error, cleanup the tmpfile and return. */
  if (! commit_err)
    return svn_io_remove_file2(lmb->tmpfile_left, FALSE, lmb->pool);

  /* There was a commit error; there is a tmpfile.  Leave the tmpfile
     around, and add message about its presence to the commit error
     chain.  Then return COMMIT_ERR.  If the conversion from UTF-8 to
     native encoding fails, we have to compose that error with the
     commit error chain, too. */

  err = svn_error_createf(commit_err->apr_err, NULL,
                          _("   '%s'"),
                          svn_dirent_local_style(lmb->tmpfile_left, pool));
  svn_error_compose(commit_err,
                    svn_error_create(commit_err->apr_err, err,
                      _("Your commit message was left in "
                        "a temporary file:")));
  return commit_err;
}