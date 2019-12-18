#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_4__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_id_t ;
struct TYPE_5__ {int /*<<< orphan*/  txn_id; int /*<<< orphan*/  copy_id; int /*<<< orphan*/  node_id; } ;
typedef  TYPE_2__ id_private_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_string_createf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_string_t *
svn_fs_base__id_unparse(const svn_fs_id_t *id,
                        apr_pool_t *pool)
{
  id_private_t *pvt = id->fsap_data;

  return svn_string_createf(pool, "%s.%s.%s",
                            pvt->node_id, pvt->copy_id, pvt->txn_id);
}