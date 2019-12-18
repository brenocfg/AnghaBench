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
struct TYPE_6__ {int (* open ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int) ;int (* close ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  DB_ENV ;
typedef  TYPE_1__ DB ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_ERR (int) ; 
 int /*<<< orphan*/  DB_BTREE ; 
 int DB_CREATE ; 
 int DB_EXCL ; 
 int ENOENT ; 
 int /*<<< orphan*/  SVN_BDB_OPEN_PARAMS (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int db_create (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int svn_fs_bdb__check_version () ; 

int
svn_fs_bdb__open_locks_table(DB **locks_p,
                             DB_ENV *env,
                             svn_boolean_t create)
{
  const u_int32_t open_flags = (create ? (DB_CREATE | DB_EXCL) : 0);
  DB *locks;
  int error;

  BDB_ERR(svn_fs_bdb__check_version());
  BDB_ERR(db_create(&locks, env, 0));
  error = (locks->open)(SVN_BDB_OPEN_PARAMS(locks, NULL),
                        "locks", 0, DB_BTREE,
                        open_flags, 0666);

  /* Create the table if it doesn't yet exist.  This is a form of
     automagical repository upgrading. */
  if (error == ENOENT && (! create))
    {
      BDB_ERR(locks->close(locks, 0));
      return svn_fs_bdb__open_locks_table(locks_p, env, TRUE);
    }
  BDB_ERR(error);

  *locks_p = locks;
  return 0;
}