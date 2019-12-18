#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
struct TYPE_8__ {TYPE_4__* fsap_data; int /*<<< orphan*/ * vtable; } ;
struct TYPE_6__ {int /*<<< orphan*/  revision; } ;
struct TYPE_7__ {TYPE_1__ rev_item; int /*<<< orphan*/  txn_id; } ;
struct TYPE_9__ {TYPE_3__ generic_id; TYPE_2__ private_id; } ;
typedef  TYPE_4__ fs_fs__id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_4__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  id_vtable ; 

svn_fs_id_t *
svn_fs_fs__id_txn_create_root(const svn_fs_fs__id_part_t *txn_id,
                              apr_pool_t *pool)
{
  fs_fs__id_t *id = apr_pcalloc(pool, sizeof(*id));

  /* node ID and copy ID are "0" */

  id->private_id.txn_id = *txn_id;
  id->private_id.rev_item.revision = SVN_INVALID_REVNUM;

  id->generic_id.vtable = &id_vtable;
  id->generic_id.fsap_data = id;

  return (svn_fs_id_t *)id;
}