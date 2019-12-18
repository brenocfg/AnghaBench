#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_7__ {TYPE_5__* fsap_data; int /*<<< orphan*/ * vtable; } ;
struct TYPE_10__ {int /*<<< orphan*/  number; int /*<<< orphan*/  revision; } ;
struct TYPE_8__ {int /*<<< orphan*/  revision; } ;
struct TYPE_9__ {TYPE_4__ rev_item; TYPE_2__ txn_id; } ;
struct TYPE_11__ {TYPE_1__ generic_id; TYPE_3__ private_id; } ;
typedef  TYPE_5__ fs_fs__id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_FS_FS__ITEM_INDEX_ROOT_NODE ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_5__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  id_vtable ; 

svn_fs_id_t *svn_fs_fs__id_create_root(const svn_revnum_t revision,
                                       apr_pool_t *pool)
{
  fs_fs__id_t *id = apr_pcalloc(pool, sizeof(*id));

  id->private_id.txn_id.revision = SVN_INVALID_REVNUM;
  id->private_id.rev_item.revision = revision;
  id->private_id.rev_item.number = SVN_FS_FS__ITEM_INDEX_ROOT_NODE;

  id->generic_id.vtable = &id_vtable;
  id->generic_id.fsap_data = id;

  return (svn_fs_id_t *)id;
}