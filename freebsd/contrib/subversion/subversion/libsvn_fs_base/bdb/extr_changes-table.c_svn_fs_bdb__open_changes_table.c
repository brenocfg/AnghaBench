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
struct TYPE_6__ {int /*<<< orphan*/  (* open ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int) ;int /*<<< orphan*/  (* set_flags ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  DB_ENV ;
typedef  TYPE_1__ DB ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DB_BTREE ; 
 int DB_CREATE ; 
 int /*<<< orphan*/  DB_DUP ; 
 int DB_EXCL ; 
 int /*<<< orphan*/  SVN_BDB_OPEN_PARAMS (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_create (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int) ; 
 int /*<<< orphan*/  svn_fs_bdb__check_version () ; 

int
svn_fs_bdb__open_changes_table(DB **changes_p,
                               DB_ENV *env,
                               svn_boolean_t create)
{
  const u_int32_t open_flags = (create ? (DB_CREATE | DB_EXCL) : 0);
  DB *changes;

  BDB_ERR(svn_fs_bdb__check_version());
  BDB_ERR(db_create(&changes, env, 0));

  /* Enable duplicate keys. This allows us to store the changes
     one-per-row.  Note: this must occur before ->open().  */
  BDB_ERR(changes->set_flags(changes, DB_DUP));

  BDB_ERR((changes->open)(SVN_BDB_OPEN_PARAMS(changes, NULL),
                          "changes", 0, DB_BTREE,
                          open_flags, 0666));

  *changes_p = changes;
  return 0;
}