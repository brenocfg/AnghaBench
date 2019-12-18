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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int apr_uintptr_t ;
typedef  scalar_t__ apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {scalar_t__ protection; } ;
typedef  TYPE_1__ apr_finfo_t ;
typedef  scalar_t__ apr_fileperms_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FINFO_PROT ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ apr_time_now () ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/ * svn_io_file_info_get (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_open_uniquely_named (int /*<<< orphan*/ **,char const**,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_file2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_default_file_perms(apr_fileperms_t *perms,
                       const char *directory,
                       apr_pool_t *scratch_pool)
{
  /* the default permissions as read from the temp folder */
  static apr_fileperms_t default_perms = 0;

  /* Technically, this "racy": Multiple threads may use enter here and
     try to figure out the default permission concurrently. That's fine
     since they will end up with the same results. Even more technical,
     apr_fileperms_t is an atomic type on 32+ bit machines.
   */
  if (default_perms == 0)
    {
      apr_finfo_t finfo;
      apr_file_t *fd;
      const char *fname_base, *fname;
      apr_uint32_t randomish;
      svn_error_t *err;

      /* Get the perms for a newly created file to find out what bits
        should be set.

        Explicitly delete the file because we want this file to be as
        short-lived as possible since its presence means other
        processes may have to try multiple names.

        Using svn_io_open_uniquely_named() here because other tempfile
        creation functions tweak the permission bits of files they create.

        Note that APR pool structures are allocated as the first item
        in their first memory page (with e.g. 4kB granularity), i.e. the
        lower bits tend to be identical between pool instances.  That is
        particularly true for the MMAPed allocator.
      */
      randomish = ((apr_uint32_t)(apr_uintptr_t)scratch_pool
                   + (apr_uint32_t)((apr_uintptr_t)scratch_pool / 4096)
                   + (apr_uint32_t)apr_time_now());
      fname_base = apr_psprintf(scratch_pool, "svn-%08x", randomish);

      SVN_ERR(svn_io_open_uniquely_named(&fd, &fname, directory, fname_base,
                                         NULL, svn_io_file_del_none,
                                         scratch_pool, scratch_pool));
      err = svn_io_file_info_get(&finfo, APR_FINFO_PROT, fd, scratch_pool);
      err = svn_error_compose_create(err, svn_io_file_close(fd, scratch_pool));
      err = svn_error_compose_create(err, svn_io_remove_file2(fname, TRUE,
                                                              scratch_pool));
      SVN_ERR(err);
      *perms = finfo.protection;
      default_perms = finfo.protection;
    }
  else
    *perms = default_perms;

  return SVN_NO_ERROR;
}