#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  z ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {int statsOn; int shellFlgs; int /*<<< orphan*/ * out; int /*<<< orphan*/ * pStmt; } ;
typedef  TYPE_1__ ShellState ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int SHFLG_Lookaside ; 
 int SHFLG_Pagecache ; 
 int /*<<< orphan*/  SQLITE_DBSTATUS_CACHE_HIT ; 
 int /*<<< orphan*/  SQLITE_DBSTATUS_CACHE_MISS ; 
 int /*<<< orphan*/  SQLITE_DBSTATUS_CACHE_SPILL ; 
 int /*<<< orphan*/  SQLITE_DBSTATUS_CACHE_USED ; 
 int /*<<< orphan*/  SQLITE_DBSTATUS_CACHE_WRITE ; 
 int /*<<< orphan*/  SQLITE_DBSTATUS_LOOKASIDE_HIT ; 
 int /*<<< orphan*/  SQLITE_DBSTATUS_LOOKASIDE_MISS_FULL ; 
 int /*<<< orphan*/  SQLITE_DBSTATUS_LOOKASIDE_MISS_SIZE ; 
 int /*<<< orphan*/  SQLITE_DBSTATUS_LOOKASIDE_USED ; 
 int /*<<< orphan*/  SQLITE_DBSTATUS_SCHEMA_USED ; 
 int /*<<< orphan*/  SQLITE_DBSTATUS_STMT_USED ; 
 int /*<<< orphan*/  SQLITE_STATUS_MALLOC_COUNT ; 
 int /*<<< orphan*/  SQLITE_STATUS_MALLOC_SIZE ; 
 int /*<<< orphan*/  SQLITE_STATUS_MEMORY_USED ; 
 int /*<<< orphan*/  SQLITE_STATUS_PAGECACHE_OVERFLOW ; 
 int /*<<< orphan*/  SQLITE_STATUS_PAGECACHE_SIZE ; 
 int /*<<< orphan*/  SQLITE_STATUS_PAGECACHE_USED ; 
 int /*<<< orphan*/  SQLITE_STATUS_PARSER_STACK ; 
 int /*<<< orphan*/  SQLITE_STMTSTATUS_AUTOINDEX ; 
 int /*<<< orphan*/  SQLITE_STMTSTATUS_FULLSCAN_STEP ; 
 int /*<<< orphan*/  SQLITE_STMTSTATUS_MEMUSED ; 
 int /*<<< orphan*/  SQLITE_STMTSTATUS_REPREPARE ; 
 int /*<<< orphan*/  SQLITE_STMTSTATUS_RUN ; 
 int /*<<< orphan*/  SQLITE_STMTSTATUS_SORT ; 
 int /*<<< orphan*/  SQLITE_STMTSTATUS_VM_STEP ; 
 int /*<<< orphan*/  displayLinuxIoStats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  displayStatLine (TYPE_1__*,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ *,char*,...) ; 
 int sqlite3_column_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_column_database_name (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_decltype (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_name (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_origin_name (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_table_name (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_db_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,...) ; 
 int sqlite3_stmt_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int display_stats(
  sqlite3 *db,                /* Database to query */
  ShellState *pArg,           /* Pointer to ShellState */
  int bReset                  /* True to reset the stats */
){
  int iCur;
  int iHiwtr;
  FILE *out;
  if( pArg==0 || pArg->out==0 ) return 0;
  out = pArg->out;

  if( pArg->pStmt && (pArg->statsOn & 2) ){
    int nCol, i, x;
    sqlite3_stmt *pStmt = pArg->pStmt;
    char z[100];
    nCol = sqlite3_column_count(pStmt);
    raw_printf(out, "%-36s %d\n", "Number of output columns:", nCol);
    for(i=0; i<nCol; i++){
      sqlite3_snprintf(sizeof(z),z,"Column %d %nname:", i, &x);
      utf8_printf(out, "%-36s %s\n", z, sqlite3_column_name(pStmt,i));
#ifndef SQLITE_OMIT_DECLTYPE
      sqlite3_snprintf(30, z+x, "declared type:");
      utf8_printf(out, "%-36s %s\n", z, sqlite3_column_decltype(pStmt, i));
#endif
#ifdef SQLITE_ENABLE_COLUMN_METADATA
      sqlite3_snprintf(30, z+x, "database name:");
      utf8_printf(out, "%-36s %s\n", z, sqlite3_column_database_name(pStmt,i));
      sqlite3_snprintf(30, z+x, "table name:");
      utf8_printf(out, "%-36s %s\n", z, sqlite3_column_table_name(pStmt,i));
      sqlite3_snprintf(30, z+x, "origin name:");
      utf8_printf(out, "%-36s %s\n", z, sqlite3_column_origin_name(pStmt,i));
#endif
    }
  }

  displayStatLine(pArg, "Memory Used:",
     "%lld (max %lld) bytes", SQLITE_STATUS_MEMORY_USED, bReset);
  displayStatLine(pArg, "Number of Outstanding Allocations:",
     "%lld (max %lld)", SQLITE_STATUS_MALLOC_COUNT, bReset);
  if( pArg->shellFlgs & SHFLG_Pagecache ){
    displayStatLine(pArg, "Number of Pcache Pages Used:",
       "%lld (max %lld) pages", SQLITE_STATUS_PAGECACHE_USED, bReset);
  }
  displayStatLine(pArg, "Number of Pcache Overflow Bytes:",
     "%lld (max %lld) bytes", SQLITE_STATUS_PAGECACHE_OVERFLOW, bReset);
  displayStatLine(pArg, "Largest Allocation:",
     "%lld bytes", SQLITE_STATUS_MALLOC_SIZE, bReset);
  displayStatLine(pArg, "Largest Pcache Allocation:",
     "%lld bytes", SQLITE_STATUS_PAGECACHE_SIZE, bReset);
#ifdef YYTRACKMAXSTACKDEPTH
  displayStatLine(pArg, "Deepest Parser Stack:",
     "%lld (max %lld)", SQLITE_STATUS_PARSER_STACK, bReset);
#endif

  if( db ){
    if( pArg->shellFlgs & SHFLG_Lookaside ){
      iHiwtr = iCur = -1;
      sqlite3_db_status(db, SQLITE_DBSTATUS_LOOKASIDE_USED,
                        &iCur, &iHiwtr, bReset);
      raw_printf(pArg->out,
              "Lookaside Slots Used:                %d (max %d)\n",
              iCur, iHiwtr);
      sqlite3_db_status(db, SQLITE_DBSTATUS_LOOKASIDE_HIT,
                        &iCur, &iHiwtr, bReset);
      raw_printf(pArg->out, "Successful lookaside attempts:       %d\n",
              iHiwtr);
      sqlite3_db_status(db, SQLITE_DBSTATUS_LOOKASIDE_MISS_SIZE,
                        &iCur, &iHiwtr, bReset);
      raw_printf(pArg->out, "Lookaside failures due to size:      %d\n",
              iHiwtr);
      sqlite3_db_status(db, SQLITE_DBSTATUS_LOOKASIDE_MISS_FULL,
                        &iCur, &iHiwtr, bReset);
      raw_printf(pArg->out, "Lookaside failures due to OOM:       %d\n",
              iHiwtr);
    }
    iHiwtr = iCur = -1;
    sqlite3_db_status(db, SQLITE_DBSTATUS_CACHE_USED, &iCur, &iHiwtr, bReset);
    raw_printf(pArg->out, "Pager Heap Usage:                    %d bytes\n",
            iCur);
    iHiwtr = iCur = -1;
    sqlite3_db_status(db, SQLITE_DBSTATUS_CACHE_HIT, &iCur, &iHiwtr, 1);
    raw_printf(pArg->out, "Page cache hits:                     %d\n", iCur);
    iHiwtr = iCur = -1;
    sqlite3_db_status(db, SQLITE_DBSTATUS_CACHE_MISS, &iCur, &iHiwtr, 1);
    raw_printf(pArg->out, "Page cache misses:                   %d\n", iCur);
    iHiwtr = iCur = -1;
    sqlite3_db_status(db, SQLITE_DBSTATUS_CACHE_WRITE, &iCur, &iHiwtr, 1);
    raw_printf(pArg->out, "Page cache writes:                   %d\n", iCur);
    iHiwtr = iCur = -1;
    sqlite3_db_status(db, SQLITE_DBSTATUS_CACHE_SPILL, &iCur, &iHiwtr, 1);
    raw_printf(pArg->out, "Page cache spills:                   %d\n", iCur);
    iHiwtr = iCur = -1;
    sqlite3_db_status(db, SQLITE_DBSTATUS_SCHEMA_USED, &iCur, &iHiwtr, bReset);
    raw_printf(pArg->out, "Schema Heap Usage:                   %d bytes\n",
            iCur);
    iHiwtr = iCur = -1;
    sqlite3_db_status(db, SQLITE_DBSTATUS_STMT_USED, &iCur, &iHiwtr, bReset);
    raw_printf(pArg->out, "Statement Heap/Lookaside Usage:      %d bytes\n",
            iCur);
  }

  if( pArg->pStmt ){
    iCur = sqlite3_stmt_status(pArg->pStmt, SQLITE_STMTSTATUS_FULLSCAN_STEP,
                               bReset);
    raw_printf(pArg->out, "Fullscan Steps:                      %d\n", iCur);
    iCur = sqlite3_stmt_status(pArg->pStmt, SQLITE_STMTSTATUS_SORT, bReset);
    raw_printf(pArg->out, "Sort Operations:                     %d\n", iCur);
    iCur = sqlite3_stmt_status(pArg->pStmt, SQLITE_STMTSTATUS_AUTOINDEX,bReset);
    raw_printf(pArg->out, "Autoindex Inserts:                   %d\n", iCur);
    iCur = sqlite3_stmt_status(pArg->pStmt, SQLITE_STMTSTATUS_VM_STEP, bReset);
    raw_printf(pArg->out, "Virtual Machine Steps:               %d\n", iCur);
    iCur = sqlite3_stmt_status(pArg->pStmt, SQLITE_STMTSTATUS_REPREPARE,bReset);
    raw_printf(pArg->out, "Reprepare operations:                %d\n", iCur);
    iCur = sqlite3_stmt_status(pArg->pStmt, SQLITE_STMTSTATUS_RUN, bReset);
    raw_printf(pArg->out, "Number of times run:                 %d\n", iCur);
    iCur = sqlite3_stmt_status(pArg->pStmt, SQLITE_STMTSTATUS_MEMUSED, bReset);
    raw_printf(pArg->out, "Memory used by prepared stmt:        %d\n", iCur);
  }

#ifdef __linux__
  displayLinuxIoStats(pArg->out);
#endif

  /* Do not remove this machine readable comment: extra-stats-output-here */

  return 0;
}