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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_open_readonly (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_wc__adm_child (char const*,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__open_adm_stream(svn_stream_t **stream,
                        const char *dir_abspath,
                        const char *fname,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  const char *local_abspath;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(dir_abspath));

  local_abspath = svn_wc__adm_child(dir_abspath, fname, scratch_pool);
  return svn_error_trace(svn_stream_open_readonly(stream, local_abspath,
                                                  result_pool, scratch_pool));
}