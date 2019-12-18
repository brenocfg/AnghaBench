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
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_file_rename2 (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_unique (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_read_specialfile (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
detranslate_special_file(const char *src, const char *dst,
                         svn_cancel_func_t cancel_func, void *cancel_baton,
                         apr_pool_t *scratch_pool)
{
  const char *dst_tmp;
  svn_stream_t *src_stream;
  svn_stream_t *dst_stream;

  /* Open a temporary destination that we will eventually atomically
     rename into place. */
  SVN_ERR(svn_stream_open_unique(&dst_stream, &dst_tmp,
                                 svn_dirent_dirname(dst, scratch_pool),
                                 svn_io_file_del_none,
                                 scratch_pool, scratch_pool));
  SVN_ERR(svn_subst_read_specialfile(&src_stream, src,
                                     scratch_pool, scratch_pool));
  SVN_ERR(svn_stream_copy3(src_stream, dst_stream,
                           cancel_func, cancel_baton, scratch_pool));

  /* Do the atomic rename from our temporary location. */
  return svn_error_trace(svn_io_file_rename2(dst_tmp, dst, FALSE, scratch_pool));
}