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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct miscellaneous_set_args {char const* key; char const* val; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * svn_fs_base__retry_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct miscellaneous_set_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_miscellaneous_set ; 

svn_error_t *
svn_fs_base__miscellaneous_set(svn_fs_t *fs,
                               const char *key,
                               const char *val,
                               apr_pool_t *pool)
{
  struct miscellaneous_set_args msa;
  msa.key = key;
  msa.val = val;

  return svn_fs_base__retry_txn(fs, txn_body_miscellaneous_set, &msa,
                                TRUE, pool);
}