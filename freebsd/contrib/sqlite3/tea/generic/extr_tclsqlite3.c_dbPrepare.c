#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_3__ {int maxStmt; int /*<<< orphan*/  db; scalar_t__ bLegacyPrepare; } ;
typedef  TYPE_1__ SqliteDb ;

/* Variables and functions */
 unsigned int SQLITE_PREPARE_PERSISTENT ; 
 int sqlite3_prepare (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ **,char const**) ; 
 int sqlite3_prepare_v3 (int /*<<< orphan*/ ,char const*,int,unsigned int,int /*<<< orphan*/ **,char const**) ; 

__attribute__((used)) static int dbPrepare(
  SqliteDb *pDb,                  /* Database object */
  const char *zSql,               /* SQL to compile */
  sqlite3_stmt **ppStmt,          /* OUT: Prepared statement */
  const char **pzOut              /* OUT: Pointer to next SQL statement */
){
  unsigned int prepFlags = 0;
#ifdef SQLITE_TEST
  if( pDb->bLegacyPrepare ){
    return sqlite3_prepare(pDb->db, zSql, -1, ppStmt, pzOut);
  }
#endif
  /* If the statement cache is large, use the SQLITE_PREPARE_PERSISTENT
  ** flags, which uses less lookaside memory.  But if the cache is small,
  ** omit that flag to make full use of lookaside */
  if( pDb->maxStmt>5 ) prepFlags = SQLITE_PREPARE_PERSISTENT;

  return sqlite3_prepare_v3(pDb->db, zSql, -1, prepFlags, ppStmt, pzOut);
}