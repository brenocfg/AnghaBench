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
typedef  int /*<<< orphan*/  svn_txdelta_stream_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  base_file_contents (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
base_get_file_delta_stream(svn_txdelta_stream_t **stream_p,
                           svn_fs_root_t *source_root,
                           const char *source_path,
                           svn_fs_root_t *target_root,
                           const char *target_path,
                           apr_pool_t *pool)
{
  svn_stream_t *source, *target;
  svn_txdelta_stream_t *delta_stream;

  /* Get read functions for the source file contents.  */
  if (source_root && source_path)
    SVN_ERR(base_file_contents(&source, source_root, source_path, pool));
  else
    source = svn_stream_empty(pool);

  /* Get read functions for the target file contents.  */
  SVN_ERR(base_file_contents(&target, target_root, target_path, pool));

  /* Create a delta stream that turns the ancestor into the target.  */
  svn_txdelta2(&delta_stream, source, target, TRUE, pool);

  *stream_p = delta_stream;
  return SVN_NO_ERROR;
}