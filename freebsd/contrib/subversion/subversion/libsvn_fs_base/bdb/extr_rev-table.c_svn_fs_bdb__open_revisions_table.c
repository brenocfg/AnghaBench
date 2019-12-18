#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* open ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int) ;} ;
typedef  int /*<<< orphan*/  DB_ENV ;
typedef  TYPE_1__ DB ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_ERR (int /*<<< orphan*/ ) ; 
 int DB_CREATE ; 
 int DB_EXCL ; 
 int /*<<< orphan*/  DB_RECNO ; 
 int /*<<< orphan*/  SVN_BDB_OPEN_PARAMS (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_create (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int) ; 
 int /*<<< orphan*/  svn_fs_bdb__check_version () ; 

int svn_fs_bdb__open_revisions_table(DB **revisions_p,
                                     DB_ENV *env,
                                     svn_boolean_t create)
{
  const u_int32_t open_flags = (create ? (DB_CREATE | DB_EXCL) : 0);
  DB *revisions;

  BDB_ERR(svn_fs_bdb__check_version());
  BDB_ERR(db_create(&revisions, env, 0));
  BDB_ERR((revisions->open)(SVN_BDB_OPEN_PARAMS(revisions, NULL),
                            "revisions", 0, DB_RECNO,
                            open_flags, 0666));

  *revisions_p = revisions;
  return 0;
}