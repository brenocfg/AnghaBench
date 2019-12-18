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
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_4__ {int /*<<< orphan*/  fs; int /*<<< orphan*/  is_txn_root; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct change_node_prop_args {char const* path; char const* name; int /*<<< orphan*/  const* value; TYPE_1__* root; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_FS__NOT_TXN (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * svn_fs_base__retry_txn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct change_node_prop_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_change_node_prop ; 

__attribute__((used)) static svn_error_t *
base_change_node_prop(svn_fs_root_t *root,
                      const char *path,
                      const char *name,
                      const svn_string_t *value,
                      apr_pool_t *pool)
{
  struct change_node_prop_args args;

  if (! root->is_txn_root)
    return SVN_FS__NOT_TXN(root);

  args.root  = root;
  args.path  = path;
  args.name  = name;
  args.value = value;
  return svn_fs_base__retry_txn(root->fs, txn_body_change_node_prop, &args,
                                TRUE, pool);
}