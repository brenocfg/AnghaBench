#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  file_path; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ set_read_only_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_finfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN__APR_FINFO_READONLY ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  set_read_only ; 
 int /*<<< orphan*/  svn_io__is_finfo_read_only (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_set_file_read_write (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_stat (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
auto_make_writable(const char *path,
                   apr_pool_t *result_pool,
                   apr_pool_t *scratch_pool)
{
  svn_boolean_t is_read_only;
  apr_finfo_t finfo;

  SVN_ERR(svn_io_stat(&finfo, path, SVN__APR_FINFO_READONLY, scratch_pool));
  SVN_ERR(svn_io__is_finfo_read_only(&is_read_only, &finfo, scratch_pool));

  if (is_read_only)
    {
      /* Tell the pool to restore the r/o state upon cleanup
         (assuming the file will still exist, failing silently otherwise). */
      set_read_only_baton_t *baton = apr_pcalloc(result_pool,
                                                  sizeof(*baton));
      baton->pool = result_pool;
      baton->file_path = apr_pstrdup(result_pool, path);
      apr_pool_cleanup_register(result_pool, baton,
                                set_read_only, apr_pool_cleanup_null);

      /* Finally, allow write access (undoing it has already been scheduled
         and is idempotent). */
      SVN_ERR(svn_io_set_file_read_write(path, FALSE, scratch_pool));
    }

  return SVN_NO_ERROR;
}