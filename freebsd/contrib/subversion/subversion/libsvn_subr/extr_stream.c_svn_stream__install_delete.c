#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct install_baton_t* baton; } ;
typedef  TYPE_2__ svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  file; } ;
struct install_baton_t {int /*<<< orphan*/  tmp_path; TYPE_1__ baton_apr; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_io__win_delete_file_on_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_file2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_stream__install_delete(svn_stream_t *install_stream,
                           apr_pool_t *scratch_pool)
{
  struct install_baton_t *ib = install_stream->baton;

#ifdef WIN32
  svn_error_t *err;

  /* Mark the file as delete on close to avoid having to reopen
     the file as part of the delete handling. */
  err = svn_io__win_delete_file_on_close(ib->baton_apr.file,  ib->tmp_path,
                                         scratch_pool);
  if (err == SVN_NO_ERROR)
    {
      SVN_ERR(svn_io_file_close(ib->baton_apr.file, scratch_pool));
      return SVN_NO_ERROR; /* File is already gone */
    }

  /* Deleting file on close may be unsupported, so ignore errors and
     fallback to svn_io_remove_file2(). */
  svn_error_clear(err);
#endif

  SVN_ERR(svn_io_file_close(ib->baton_apr.file, scratch_pool));

  return svn_error_trace(svn_io_remove_file2(ib->tmp_path, FALSE,
                                             scratch_pool));
}