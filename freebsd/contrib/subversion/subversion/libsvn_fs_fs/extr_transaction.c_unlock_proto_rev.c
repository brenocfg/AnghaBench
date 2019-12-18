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
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct unlock_proto_rev_baton {void* lockcookie; int /*<<< orphan*/  txn_id; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  unlock_proto_rev_body ; 
 int /*<<< orphan*/ * with_txnlist_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct unlock_proto_rev_baton*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
unlock_proto_rev(svn_fs_t *fs,
                 const svn_fs_fs__id_part_t *txn_id,
                 void *lockcookie,
                 apr_pool_t *pool)
{
  struct unlock_proto_rev_baton b;

  b.txn_id = *txn_id;
  b.lockcookie = lockcookie;
  return with_txnlist_lock(fs, unlock_proto_rev_body, &b, pool);
}