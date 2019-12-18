#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_14__ {int /*<<< orphan*/  db_txn; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_15__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  idx ;
struct TYPE_16__ {TYPE_5__* uuids; } ;
typedef  TYPE_3__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_18__ {int /*<<< orphan*/  (* put ) (TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {int* data; int size; } ;
typedef  TYPE_4__ DBT ;
typedef  TYPE_5__ DB ;

/* Variables and functions */
 int /*<<< orphan*/ * BDB_WRAP (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int* apr_pstrmemdup (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__clear_dbt (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_fs_base__trail_debug (TYPE_1__*,char*,char*) ; 

svn_error_t *svn_fs_bdb__set_uuid(svn_fs_t *fs,
                                  int idx,
                                  const char *uuid,
                                  trail_t *trail,
                                  apr_pool_t *pool)
{
  base_fs_data_t *bfd = fs->fsap_data;
  DB *uuids = bfd->uuids;
  DBT key;
  DBT value;

  svn_fs_base__clear_dbt(&key);
  key.data = &idx;
  key.size = sizeof(idx);

  svn_fs_base__clear_dbt(&value);
  value.size = (u_int32_t) strlen(uuid);
  value.data = apr_pstrmemdup(pool, uuid, value.size + 1);

  svn_fs_base__trail_debug(trail, "uuids", "put");
  return BDB_WRAP(fs, N_("set repository uuid"),
                  uuids->put(uuids, trail->db_txn, &key, &value, 0));
}