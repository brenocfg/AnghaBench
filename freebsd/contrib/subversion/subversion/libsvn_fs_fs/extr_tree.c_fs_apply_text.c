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
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
struct text_baton_t {int /*<<< orphan*/ * stream; int /*<<< orphan*/  result_checksum; int /*<<< orphan*/ * pool; int /*<<< orphan*/  path; int /*<<< orphan*/ * root; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apply_text (struct text_baton_t*,int /*<<< orphan*/ *) ; 
 struct text_baton_t* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_checksum_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
fs_apply_text(svn_stream_t **contents_p,
              svn_fs_root_t *root,
              const char *path,
              svn_checksum_t *result_checksum,
              apr_pool_t *pool)
{
  struct text_baton_t *tb = apr_pcalloc(pool, sizeof(*tb));

  tb->root = root;
  tb->path = svn_fs__canonicalize_abspath(path, pool);
  tb->pool = pool;
  tb->result_checksum = svn_checksum_dup(result_checksum, pool);

  SVN_ERR(apply_text(tb, pool));

  *contents_p = tb->stream;
  return SVN_NO_ERROR;
}