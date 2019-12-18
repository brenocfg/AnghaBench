#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_7__ {int (* open ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int) ;int (* close ) (TYPE_1__*,int /*<<< orphan*/ ) ;int (* put ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  DB_ENV ;
typedef  int /*<<< orphan*/  DBT ;
typedef  TYPE_1__ DB ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_ERR (int) ; 
 int /*<<< orphan*/  DB_BTREE ; 
 int DB_CREATE ; 
 int DB_EXCL ; 
 int ENOENT ; 
 char* NEXT_KEY_KEY ; 
 int /*<<< orphan*/  SVN_BDB_OPEN_PARAMS (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int db_create (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int stub3 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__str_to_dbt (int /*<<< orphan*/ *,char*) ; 
 int svn_fs_bdb__check_version () ; 

int svn_fs_bdb__open_checksum_reps_table(DB **checksum_reps_p,
                                         DB_ENV *env,
                                         svn_boolean_t create)
{
  const u_int32_t open_flags = (create ? (DB_CREATE | DB_EXCL) : 0);
  DB *checksum_reps;
  int error;

  BDB_ERR(svn_fs_bdb__check_version());
  BDB_ERR(db_create(&checksum_reps, env, 0));
  error = (checksum_reps->open)(SVN_BDB_OPEN_PARAMS(checksum_reps, NULL),
                                "checksum-reps", 0, DB_BTREE,
                                open_flags, 0666);

  /* Create the checksum-reps table if it doesn't exist. */
  if (error == ENOENT && (! create))
    {
      BDB_ERR(checksum_reps->close(checksum_reps, 0));
      return svn_fs_bdb__open_checksum_reps_table(checksum_reps_p, env, TRUE);
    }

  /* Create the initial `next-key' table entry.  */
  if (create)
    {
      DBT key, value;
      BDB_ERR(checksum_reps->put(checksum_reps, 0,
                                 svn_fs_base__str_to_dbt(&key, NEXT_KEY_KEY),
                                 svn_fs_base__str_to_dbt(&value, "0"), 0));
    }

  BDB_ERR(error);

  *checksum_reps_p = checksum_reps;
  return 0;
}