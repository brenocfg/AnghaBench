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
struct TYPE_3__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct make_file_args {char const* path; TYPE_1__* root; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * svn_fs_base__retry_txn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct make_file_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_make_file ; 

__attribute__((used)) static svn_error_t *
base_make_file(svn_fs_root_t *root,
               const char *path,
               apr_pool_t *pool)
{
  struct make_file_args args;

  args.root = root;
  args.path = path;
  return svn_fs_base__retry_txn(root->fs, txn_body_make_file, &args,
                                TRUE, pool);
}