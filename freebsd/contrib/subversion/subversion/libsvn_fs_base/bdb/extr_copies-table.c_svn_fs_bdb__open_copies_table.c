#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* put ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* open ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int) ;} ;
typedef  int /*<<< orphan*/  DB_ENV ;
typedef  int /*<<< orphan*/  DBT ;
typedef  TYPE_1__ DB ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DB_BTREE ; 
 int DB_CREATE ; 
 int DB_EXCL ; 
 char* NEXT_KEY_KEY ; 
 int /*<<< orphan*/  SVN_BDB_OPEN_PARAMS (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_create (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__str_to_dbt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_fs_bdb__check_version () ; 

int
svn_fs_bdb__open_copies_table(DB **copies_p,
                              DB_ENV *env,
                              svn_boolean_t create)
{
  const u_int32_t open_flags = (create ? (DB_CREATE | DB_EXCL) : 0);
  DB *copies;

  BDB_ERR(svn_fs_bdb__check_version());
  BDB_ERR(db_create(&copies, env, 0));
  BDB_ERR((copies->open)(SVN_BDB_OPEN_PARAMS(copies, NULL),
                         "copies", 0, DB_BTREE,
                         open_flags, 0666));

  /* Create the initial `next-key' table entry.  */
  if (create)
  {
    DBT key, value;
    BDB_ERR(copies->put(copies, 0,
                        svn_fs_base__str_to_dbt(&key, NEXT_KEY_KEY),
                        svn_fs_base__str_to_dbt(&value, "0"), 0));
  }

  *copies_p = copies;
  return 0;
}