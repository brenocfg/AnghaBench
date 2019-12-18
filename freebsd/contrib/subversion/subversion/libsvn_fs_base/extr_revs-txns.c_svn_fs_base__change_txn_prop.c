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
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_3__ {int /*<<< orphan*/  id; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ svn_fs_txn_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct change_txn_prop_args {char const* name; int /*<<< orphan*/  const* value; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs__check_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__retry_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct change_txn_prop_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_change_txn_prop ; 

svn_error_t *
svn_fs_base__change_txn_prop(svn_fs_txn_t *txn,
                             const char *name,
                             const svn_string_t *value,
                             apr_pool_t *pool)
{
  struct change_txn_prop_args args;
  svn_fs_t *fs = txn->fs;

  SVN_ERR(svn_fs__check_fs(fs, TRUE));

  args.id = txn->id;
  args.name = name;
  args.value = value;
  return svn_fs_base__retry_txn(fs, txn_body_change_txn_prop, &args,
                                TRUE, pool);
}