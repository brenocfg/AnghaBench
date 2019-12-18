#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_6__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {char const* path; int /*<<< orphan*/ * file_stream; int /*<<< orphan*/ * pool; TYPE_1__* root; } ;
typedef  TYPE_2__ file_contents_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_fs_base__retry_txn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_get_file_contents ; 

__attribute__((used)) static svn_error_t *
base_file_contents(svn_stream_t **contents,
                   svn_fs_root_t *root,
                   const char *path,
                   apr_pool_t *pool)
{
  file_contents_baton_t *fb = apr_pcalloc(pool, sizeof(*fb));
  fb->root = root;
  fb->path = path;
  fb->pool = pool;

  /* Create the readable stream in the context of a db txn.  */
  SVN_ERR(svn_fs_base__retry_txn(root->fs, txn_body_get_file_contents, fb,
                                 FALSE, pool));

  *contents = fb->file_stream;
  return SVN_NO_ERROR;
}