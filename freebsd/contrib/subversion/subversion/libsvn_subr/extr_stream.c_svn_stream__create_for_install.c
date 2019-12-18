#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct install_baton_t* baton; } ;
typedef  TYPE_1__ svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct baton_apr {int dummy; } ;
struct install_baton_t {char const* tmp_path; struct baton_apr baton_apr; } ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int APR_BINARY ; 
 int APR_BUFFERED ; 
 int APR_WRITE ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ apr_os_file_put (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 struct install_baton_t* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  create_tempfile (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  install_close ; 
 char* svn_dirent_internal_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ **,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stream__from_aprfile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (TYPE_1__*,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_stream__create_for_install(svn_stream_t **install_stream,
                               const char *tmp_abspath,
                               apr_pool_t *result_pool,
                               apr_pool_t *scratch_pool)
{
  apr_file_t *file;
  struct install_baton_t *ib;
  const char *tmp_path;

#ifdef WIN32
  HANDLE hInstall;
  apr_status_t status;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(tmp_abspath));

  SVN_ERR(create_tempfile(&hInstall, &tmp_path, tmp_abspath,
                          scratch_pool, scratch_pool));

  /* Wrap as a standard APR file to allow sharing implementation.

     But do note that some file functions (such as retrieving the name)
     don't work on this wrapper.
     Use buffered mode to match svn_io_open_unique_file3() behavior. */
  status = apr_os_file_put(&file, &hInstall,
                           APR_WRITE | APR_BINARY | APR_BUFFERED,
                           result_pool);

  if (status)
    {
      CloseHandle(hInstall);
      return svn_error_wrap_apr(status, NULL);
    }

  tmp_path = svn_dirent_internal_style(tmp_path, result_pool);
#else

  SVN_ERR_ASSERT(svn_dirent_is_absolute(tmp_abspath));

  SVN_ERR(svn_io_open_unique_file3(&file, &tmp_path, tmp_abspath,
                                   svn_io_file_del_none,
                                   result_pool, scratch_pool));
#endif
  /* Set the temporary file to be truncated on seeks. */
  *install_stream = svn_stream__from_aprfile(file, FALSE, TRUE,
                                             result_pool);

  ib = apr_pcalloc(result_pool, sizeof(*ib));
  ib->baton_apr = *(struct baton_apr*)(*install_stream)->baton;

  assert((void*)&ib->baton_apr == (void*)ib); /* baton pointer is the same */

  (*install_stream)->baton = ib;

  ib->tmp_path = tmp_path;

  /* Don't close the file on stream close; flush instead */
  svn_stream_set_close(*install_stream, install_close);

  return SVN_NO_ERROR;
}