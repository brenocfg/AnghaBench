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
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DEPTH_INFINITY_OR_FILES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_client_diff4 (int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_diff3(const apr_array_header_t *options,
                 const char *path1,
                 const svn_opt_revision_t *revision1,
                 const char *path2,
                 const svn_opt_revision_t *revision2,
                 svn_boolean_t recurse,
                 svn_boolean_t ignore_ancestry,
                 svn_boolean_t no_diff_deleted,
                 svn_boolean_t ignore_content_type,
                 const char *header_encoding,
                 apr_file_t *outfile,
                 apr_file_t *errfile,
                 svn_client_ctx_t *ctx,
                 apr_pool_t *pool)
{
  return svn_client_diff4(options, path1, revision1, path2,
                          revision2, NULL,
                          SVN_DEPTH_INFINITY_OR_FILES(recurse),
                          ignore_ancestry, no_diff_deleted,
                          ignore_content_type, header_encoding,
                          outfile, errfile, NULL, ctx, pool);
}