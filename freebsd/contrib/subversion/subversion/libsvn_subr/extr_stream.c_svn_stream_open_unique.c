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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_io_file_del_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ **,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_stream_open_unique(svn_stream_t **stream,
                       const char **temp_path,
                       const char *dirpath,
                       svn_io_file_del_t delete_when,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  apr_file_t *file;

  SVN_ERR(svn_io_open_unique_file3(&file, temp_path, dirpath,
                                   delete_when, result_pool, scratch_pool));
  *stream = svn_stream_from_aprfile2(file, FALSE, result_pool);

  return SVN_NO_ERROR;
}