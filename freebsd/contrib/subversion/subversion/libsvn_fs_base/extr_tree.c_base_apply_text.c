#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_3__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
struct text_baton_t {char const* path; int /*<<< orphan*/ * stream; int /*<<< orphan*/  result_checksum; int /*<<< orphan*/ * pool; TYPE_1__* root; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct text_baton_t* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_checksum_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__retry_txn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct text_baton_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_apply_text ; 

__attribute__((used)) static svn_error_t *
base_apply_text(svn_stream_t **contents_p,
                svn_fs_root_t *root,
                const char *path,
                svn_checksum_t *result_checksum,
                apr_pool_t *pool)
{
  struct text_baton_t *tb = apr_pcalloc(pool, sizeof(*tb));

  tb->root = root;
  tb->path = path;
  tb->pool = pool;
  tb->result_checksum = svn_checksum_dup(result_checksum, pool);

  SVN_ERR(svn_fs_base__retry_txn(root->fs, txn_body_apply_text, tb,
                                 FALSE, pool));

  *contents_p = tb->stream;
  return SVN_NO_ERROR;
}