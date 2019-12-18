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
struct TYPE_4__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct txn_proplist_args {char const* id; int /*<<< orphan*/ ** table_p; } ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txn_body_txn_proplist (struct txn_proplist_args*,TYPE_1__*) ; 

svn_error_t *
svn_fs_base__txn_proplist_in_trail(apr_hash_t **table_p,
                                   const char *txn_id,
                                   trail_t *trail)
{
  struct txn_proplist_args args;
  apr_hash_t *table;

  args.table_p = &table;
  args.id = txn_id;
  SVN_ERR(txn_body_txn_proplist(&args, trail));

  *table_p = table ? table : apr_hash_make(trail->pool);
  return SVN_NO_ERROR;
}