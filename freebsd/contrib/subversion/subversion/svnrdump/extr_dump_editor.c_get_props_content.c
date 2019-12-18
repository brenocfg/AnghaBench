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
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_repos__dumpfile_headers_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_PROP_DELTA ; 
 int /*<<< orphan*/  svn_hash_write_incremental (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rdump__normalize_props (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__dumpfile_header_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_stringbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_props_content(svn_repos__dumpfile_headers_t *headers,
                  svn_stringbuf_t **content,
                  apr_hash_t *props,
                  apr_hash_t *deleted_props,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  svn_stream_t *content_stream;
  apr_hash_t *normal_props;

  *content = svn_stringbuf_create_empty(result_pool);

  content_stream = svn_stream_from_stringbuf(*content, scratch_pool);

  SVN_ERR(svn_rdump__normalize_props(&normal_props, props, scratch_pool));
  SVN_ERR(svn_hash_write_incremental(normal_props, deleted_props,
                                     content_stream, "PROPS-END",
                                     scratch_pool));
  SVN_ERR(svn_stream_close(content_stream));

  /* Prop-delta: true */
  svn_repos__dumpfile_header_push(
    headers, SVN_REPOS_DUMPFILE_PROP_DELTA, "true");

  return SVN_NO_ERROR;
}