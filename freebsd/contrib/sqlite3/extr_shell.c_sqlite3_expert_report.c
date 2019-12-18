#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bRun; char* zCandidates; TYPE_2__* pStatement; } ;
typedef  TYPE_1__ sqlite3expert ;
struct TYPE_5__ {int iId; char* zSql; char* zIdx; char* zEQP; struct TYPE_5__* pNext; } ;
typedef  TYPE_2__ IdxStatement ;

/* Variables and functions */
#define  EXPERT_REPORT_CANDIDATES 131 
#define  EXPERT_REPORT_INDEXES 130 
#define  EXPERT_REPORT_PLAN 129 
#define  EXPERT_REPORT_SQL 128 

const char *sqlite3_expert_report(sqlite3expert *p, int iStmt, int eReport){
  const char *zRet = 0;
  IdxStatement *pStmt;

  if( p->bRun==0 ) return 0;
  for(pStmt=p->pStatement; pStmt && pStmt->iId!=iStmt; pStmt=pStmt->pNext);
  switch( eReport ){
    case EXPERT_REPORT_SQL:
      if( pStmt ) zRet = pStmt->zSql;
      break;
    case EXPERT_REPORT_INDEXES:
      if( pStmt ) zRet = pStmt->zIdx;
      break;
    case EXPERT_REPORT_PLAN:
      if( pStmt ) zRet = pStmt->zEQP;
      break;
    case EXPERT_REPORT_CANDIDATES:
      zRet = p->zCandidates;
      break;
  }
  return zRet;
}