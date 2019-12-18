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
struct TYPE_3__ {void* lockcookie; int /*<<< orphan*/  txn_id; } ;
typedef  TYPE_1__ unlock_proto_rev_baton_t ;
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  unlock_proto_rev_body ; 
 int /*<<< orphan*/ * with_txnlist_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
unlock_proto_rev(svn_fs_t *fs,
                 svn_fs_x__txn_id_t txn_id,
                 void *lockcookie,
                 apr_pool_t *scratch_pool)
{
  unlock_proto_rev_baton_t b;

  b.txn_id = txn_id;
  b.lockcookie = lockcookie;
  return with_txnlist_lock(fs, unlock_proto_rev_body, &b, scratch_pool);
}