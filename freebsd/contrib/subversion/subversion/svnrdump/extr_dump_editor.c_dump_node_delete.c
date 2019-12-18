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
typedef  int /*<<< orphan*/  svn_repos__dumpfile_headers_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_NODE_ACTION ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_NODE_PATH ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_relpath_is_canonical (char const*) ; 
 int /*<<< orphan*/  svn_repos__dump_node_record (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__dumpfile_header_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_repos__dumpfile_headers_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
dump_node_delete(svn_stream_t *stream,
                 const char *node_relpath,
                 apr_pool_t *pool)
{
  svn_repos__dumpfile_headers_t *headers
    = svn_repos__dumpfile_headers_create(pool);

  assert(svn_relpath_is_canonical(node_relpath));

  /* Node-path: ... */
  svn_repos__dumpfile_header_push(
    headers, SVN_REPOS_DUMPFILE_NODE_PATH, node_relpath);

  /* Node-action: delete */
  svn_repos__dumpfile_header_push(
    headers, SVN_REPOS_DUMPFILE_NODE_ACTION, "delete");

  SVN_ERR(svn_repos__dump_node_record(stream, headers,
                                      NULL, FALSE, 0,  /* props & text */
                                      FALSE /*content_length_always*/, pool));
  return SVN_NO_ERROR;
}