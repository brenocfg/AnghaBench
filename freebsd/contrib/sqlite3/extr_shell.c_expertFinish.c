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
typedef  int /*<<< orphan*/  sqlite3expert ;
struct TYPE_4__ {int bVerbose; int /*<<< orphan*/ * pExpert; } ;
struct TYPE_5__ {TYPE_1__ expert; int /*<<< orphan*/ * out; } ;
typedef  TYPE_2__ ShellState ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXPERT_REPORT_CANDIDATES ; 
 int /*<<< orphan*/  EXPERT_REPORT_INDEXES ; 
 int /*<<< orphan*/  EXPERT_REPORT_PLAN ; 
 int /*<<< orphan*/  EXPERT_REPORT_SQL ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ *,char*,...) ; 
 int sqlite3_expert_analyze (int /*<<< orphan*/ *,char**) ; 
 int sqlite3_expert_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_expert_destroy (int /*<<< orphan*/ *) ; 
 char* sqlite3_expert_report (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int expertFinish(
  ShellState *pState,
  int bCancel,
  char **pzErr
){
  int rc = SQLITE_OK;
  sqlite3expert *p = pState->expert.pExpert;
  assert( p );
  assert( bCancel || pzErr==0 || *pzErr==0 );
  if( bCancel==0 ){
    FILE *out = pState->out;
    int bVerbose = pState->expert.bVerbose;

    rc = sqlite3_expert_analyze(p, pzErr);
    if( rc==SQLITE_OK ){
      int nQuery = sqlite3_expert_count(p);
      int i;

      if( bVerbose ){
        const char *zCand = sqlite3_expert_report(p,0,EXPERT_REPORT_CANDIDATES);
        raw_printf(out, "-- Candidates -----------------------------\n");
        raw_printf(out, "%s\n", zCand);
      }
      for(i=0; i<nQuery; i++){
        const char *zSql = sqlite3_expert_report(p, i, EXPERT_REPORT_SQL);
        const char *zIdx = sqlite3_expert_report(p, i, EXPERT_REPORT_INDEXES);
        const char *zEQP = sqlite3_expert_report(p, i, EXPERT_REPORT_PLAN);
        if( zIdx==0 ) zIdx = "(no new indexes)\n";
        if( bVerbose ){
          raw_printf(out, "-- Query %d --------------------------------\n",i+1);
          raw_printf(out, "%s\n\n", zSql);
        }
        raw_printf(out, "%s\n", zIdx);
        raw_printf(out, "%s\n", zEQP);
      }
    }
  }
  sqlite3_expert_destroy(p);
  pState->expert.pExpert = 0;
  return rc;
}