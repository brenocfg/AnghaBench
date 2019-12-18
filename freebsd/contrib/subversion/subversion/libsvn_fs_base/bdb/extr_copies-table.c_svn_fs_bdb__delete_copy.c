#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  db_txn; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_11__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_12__ {TYPE_8__* copies; } ;
typedef  TYPE_3__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_13__ {int (* del ) (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  DBT ;

/* Variables and functions */
 int /*<<< orphan*/ * BDB_WRAP (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int DB_NOTFOUND ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int stub1 (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__err_no_such_copy (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__str_to_dbt (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__trail_debug (TYPE_1__*,char*,char*) ; 

svn_error_t *
svn_fs_bdb__delete_copy(svn_fs_t *fs,
                        const char *copy_id,
                        trail_t *trail,
                        apr_pool_t *pool)
{
  base_fs_data_t *bfd = fs->fsap_data;
  DBT key;
  int db_err;

  svn_fs_base__str_to_dbt(&key, copy_id);
  svn_fs_base__trail_debug(trail, "copies", "del");
  db_err = bfd->copies->del(bfd->copies, trail->db_txn, &key, 0);
  if (db_err == DB_NOTFOUND)
    return svn_fs_base__err_no_such_copy(fs, copy_id);
  return BDB_WRAP(fs, N_("deleting entry from 'copies' table"), db_err);
}