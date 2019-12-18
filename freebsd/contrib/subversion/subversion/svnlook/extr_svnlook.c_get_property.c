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
struct TYPE_3__ {int /*<<< orphan*/  rev_id; int /*<<< orphan*/  fs; int /*<<< orphan*/  txn; int /*<<< orphan*/  is_revision; } ;
typedef  TYPE_1__ svnlook_ctxt_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs_revision_prop2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_txn_prop (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_property(svn_string_t **prop_value,
             svnlook_ctxt_t *c,
             const char *prop_name,
             apr_pool_t *pool)
{
  svn_string_t *raw_value;

  /* Fetch transaction property... */
  if (! c->is_revision)
    SVN_ERR(svn_fs_txn_prop(&raw_value, c->txn, prop_name, pool));

  /* ...or revision property -- it's your call. */
  else
    SVN_ERR(svn_fs_revision_prop2(&raw_value, c->fs, c->rev_id,
                                  prop_name, TRUE, pool, pool));

  *prop_value = raw_value;

  return SVN_NO_ERROR;
}