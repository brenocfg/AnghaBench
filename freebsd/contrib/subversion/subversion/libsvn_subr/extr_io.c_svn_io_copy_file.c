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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int /*<<< orphan*/  APR_READ ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ copy_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_copy_perms (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_rename2 (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_file2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_copy_file(const char *src,
                 const char *dst,
                 svn_boolean_t copy_perms,
                 apr_pool_t *pool)
{
  apr_file_t *from_file, *to_file;
  apr_status_t apr_err;
  const char *dst_tmp;
  svn_error_t *err;

  /* ### NOTE: sometimes src == dst. In this case, because we copy to a
     ###   temporary file, and then rename over the top of the destination,
     ###   the net result is resetting the permissions on src/dst.
     ###
     ### Note: specifically, this can happen during a switch when the desired
     ###   permissions for a file change from one branch to another. See
     ###   switch_tests 17.
     ###
     ### ... yes, we should avoid copying to the same file, and we should
     ###     make the "reset perms" explicit. The switch *happens* to work
     ###     because of this copy-to-temp-then-rename implementation. If it
     ###     weren't for that, the switch would break.
  */
#ifdef CHECK_FOR_SAME_FILE
  if (strcmp(src, dst) == 0)
    return SVN_NO_ERROR;
#endif

  SVN_ERR(svn_io_file_open(&from_file, src, APR_READ,
                           APR_OS_DEFAULT, pool));

  /* For atomicity, we copy to a tmp file and then rename the tmp
     file over the real destination. */

  SVN_ERR(svn_io_open_unique_file3(&to_file, &dst_tmp,
                                   svn_dirent_dirname(dst, pool),
                                   svn_io_file_del_none, pool, pool));

  apr_err = copy_contents(from_file, to_file, pool);

  if (apr_err)
    {
      err = svn_error_wrap_apr(apr_err, _("Can't copy '%s' to '%s'"),
                               svn_dirent_local_style(src, pool),
                               svn_dirent_local_style(dst_tmp, pool));
    }
   else
     err = NULL;

  err = svn_error_compose_create(err,
                                 svn_io_file_close(from_file, pool));

  err = svn_error_compose_create(err,
                                 svn_io_file_close(to_file, pool));

  if (err)
    {
      return svn_error_compose_create(
                                 err,
                                 svn_io_remove_file2(dst_tmp, TRUE, pool));
    }

  /* If copying perms, set the perms on dst_tmp now, so they will be
     atomically inherited in the upcoming rename.  But note that we
     had to wait until now to set perms, because if they say
     read-only, then we'd have failed filling dst_tmp's contents. */
  if (copy_perms)
    SVN_ERR(svn_io_copy_perms(src, dst_tmp, pool));

  return svn_error_trace(svn_io_file_rename2(dst_tmp, dst, FALSE, pool));
}