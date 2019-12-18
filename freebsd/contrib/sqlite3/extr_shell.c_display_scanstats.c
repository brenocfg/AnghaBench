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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_6__ {int /*<<< orphan*/  out; int /*<<< orphan*/ * pStmt; } ;
typedef  TYPE_1__ sqlite3 ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_SCANSTAT_EST ; 
 int /*<<< orphan*/  SQLITE_SCANSTAT_EXPLAIN ; 
 int /*<<< orphan*/  SQLITE_SCANSTAT_NLOOP ; 
 int /*<<< orphan*/  SQLITE_SCANSTAT_NVISIT ; 
 int /*<<< orphan*/  SQLITE_SCANSTAT_SELECTID ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (TYPE_1__*) ; 
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ sqlite3_stmt_scanstatus (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ ,char*,int,char const*) ; 

__attribute__((used)) static void display_scanstats(
  sqlite3 *db,                    /* Database to query */
  ShellState *pArg                /* Pointer to ShellState */
){
#ifndef SQLITE_ENABLE_STMT_SCANSTATUS
  UNUSED_PARAMETER(db);
  UNUSED_PARAMETER(pArg);
#else
  int i, k, n, mx;
  raw_printf(pArg->out, "-------- scanstats --------\n");
  mx = 0;
  for(k=0; k<=mx; k++){
    double rEstLoop = 1.0;
    for(i=n=0; 1; i++){
      sqlite3_stmt *p = pArg->pStmt;
      sqlite3_int64 nLoop, nVisit;
      double rEst;
      int iSid;
      const char *zExplain;
      if( sqlite3_stmt_scanstatus(p, i, SQLITE_SCANSTAT_NLOOP, (void*)&nLoop) ){
        break;
      }
      sqlite3_stmt_scanstatus(p, i, SQLITE_SCANSTAT_SELECTID, (void*)&iSid);
      if( iSid>mx ) mx = iSid;
      if( iSid!=k ) continue;
      if( n==0 ){
        rEstLoop = (double)nLoop;
        if( k>0 ) raw_printf(pArg->out, "-------- subquery %d -------\n", k);
      }
      n++;
      sqlite3_stmt_scanstatus(p, i, SQLITE_SCANSTAT_NVISIT, (void*)&nVisit);
      sqlite3_stmt_scanstatus(p, i, SQLITE_SCANSTAT_EST, (void*)&rEst);
      sqlite3_stmt_scanstatus(p, i, SQLITE_SCANSTAT_EXPLAIN, (void*)&zExplain);
      utf8_printf(pArg->out, "Loop %2d: %s\n", n, zExplain);
      rEstLoop *= rEst;
      raw_printf(pArg->out,
          "         nLoop=%-8lld nRow=%-8lld estRow=%-8lld estRow/Loop=%-8g\n",
          nLoop, nVisit, (sqlite3_int64)(rEstLoop+0.5), rEst
      );
    }
  }
  raw_printf(pArg->out, "---------------------------\n");
#endif
}