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
typedef  int /*<<< orphan*/  svn_repos__dumpfile_headers_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct dump_edit_baton {int /*<<< orphan*/  stream; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_NODE_ACTION ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_NODE_KIND ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_NODE_PATH ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_props_content (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__dump_node_record (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__dumpfile_header_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_repos__dumpfile_headers_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_puts (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static svn_error_t *
dump_mkdir(struct dump_edit_baton *eb,
           const char *repos_relpath,
           apr_pool_t *pool)
{
  svn_stringbuf_t *prop_content;
  svn_repos__dumpfile_headers_t *headers
    = svn_repos__dumpfile_headers_create(pool);

  /* Node-path: ... */
  svn_repos__dumpfile_header_push(
    headers, SVN_REPOS_DUMPFILE_NODE_PATH, repos_relpath);

  /* Node-kind: dir */
  svn_repos__dumpfile_header_push(
    headers, SVN_REPOS_DUMPFILE_NODE_KIND, "dir");

  /* Node-action: add */
  svn_repos__dumpfile_header_push(
    headers, SVN_REPOS_DUMPFILE_NODE_ACTION, "add");

  /* Dump the (empty) property block. */
  SVN_ERR(get_props_content(headers, &prop_content,
                            apr_hash_make(pool), apr_hash_make(pool),
                            pool, pool));
  SVN_ERR(svn_repos__dump_node_record(eb->stream, headers, prop_content,
                                      FALSE, 0, FALSE /*content_length_always*/,
                                      pool));

  /* Newlines to tie it all off. */
  SVN_ERR(svn_stream_puts(eb->stream, "\n\n"));

  return SVN_NO_ERROR;
}