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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__revision_file_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  item_index; int /*<<< orphan*/  revision; int /*<<< orphan*/  txn_id; } ;
typedef  TYPE_1__ representation_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * open_and_seek_revision (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * open_and_seek_transaction (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__id_txn_used (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_and_seek_representation(svn_fs_fs__revision_file_t **file_p,
                             svn_fs_t *fs,
                             representation_t *rep,
                             apr_pool_t *pool)
{
  if (! svn_fs_fs__id_txn_used(&rep->txn_id))
    return open_and_seek_revision(file_p, fs, rep->revision, rep->item_index,
                                  pool);
  else
    return open_and_seek_transaction(file_p, fs, rep, pool);
}