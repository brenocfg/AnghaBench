#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* result_checksum; void* base_checksum; int /*<<< orphan*/ * pool; int /*<<< orphan*/  path; int /*<<< orphan*/ * root; } ;
typedef  TYPE_1__ txdelta_baton_t ;
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apply_textdelta (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* svn_checksum_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  window_consumer ; 

__attribute__((used)) static svn_error_t *
x_apply_textdelta(svn_txdelta_window_handler_t *contents_p,
                  void **contents_baton_p,
                  svn_fs_root_t *root,
                  const char *path,
                  svn_checksum_t *base_checksum,
                  svn_checksum_t *result_checksum,
                  apr_pool_t *pool)
{
  apr_pool_t *scratch_pool = svn_pool_create(pool);
  txdelta_baton_t *tb = apr_pcalloc(pool, sizeof(*tb));

  tb->root = root;
  tb->path = svn_fs__canonicalize_abspath(path, pool);
  tb->pool = pool;
  tb->base_checksum = svn_checksum_dup(base_checksum, pool);
  tb->result_checksum = svn_checksum_dup(result_checksum, pool);

  SVN_ERR(apply_textdelta(tb, scratch_pool));

  *contents_p = window_consumer;
  *contents_baton_p = tb;

  svn_pool_destroy(scratch_pool);
  return SVN_NO_ERROR;
}