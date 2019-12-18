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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct change_rev_prop_args {char const* name; int /*<<< orphan*/  const* value; int /*<<< orphan*/  const* const* old_value_p; int /*<<< orphan*/  rev; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs__check_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__retry_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct change_rev_prop_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_change_rev_prop ; 

svn_error_t *
svn_fs_base__change_rev_prop(svn_fs_t *fs,
                             svn_revnum_t rev,
                             const char *name,
                             const svn_string_t *const *old_value_p,
                             const svn_string_t *value,
                             apr_pool_t *pool)
{
  struct change_rev_prop_args args;

  SVN_ERR(svn_fs__check_fs(fs, TRUE));

  args.rev = rev;
  args.name = name;
  args.old_value_p = old_value_p;
  args.value = value;
  return svn_fs_base__retry_txn(fs, txn_body_change_rev_prop, &args,
                                TRUE, pool);
}