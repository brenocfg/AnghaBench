#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_15__ {scalar_t__ pExpert; } ;
struct TYPE_16__ {scalar_t__ autoEQP; scalar_t__ cMode; scalar_t__ mode; int /*<<< orphan*/ * pStmt; scalar_t__ scanstatsOn; scalar_t__ statsOn; scalar_t__ autoExplain; int /*<<< orphan*/  out; scalar_t__ cnt; TYPE_1__ expert; int /*<<< orphan*/ * db; } ;
typedef  TYPE_2__ ShellState ;

/* Variables and functions */
 scalar_t__ AUTOEQP_full ; 
 scalar_t__ AUTOEQP_trigger ; 
 scalar_t__ IsSpace (char const) ; 
 scalar_t__ MODE_EQP ; 
 scalar_t__ MODE_Explain ; 
 int /*<<< orphan*/  SHFLG_Echo ; 
 int /*<<< orphan*/  SQLITE_DBCONFIG_TRIGGER_EQP ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 scalar_t__ ShellHasFlag (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_prepared_stmt (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_debug_trace_modes () ; 
 int /*<<< orphan*/  display_scanstats (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  display_stats (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eqp_append (TYPE_2__*,int,int,char const*) ; 
 int /*<<< orphan*/  eqp_render (TYPE_2__*) ; 
 int /*<<< orphan*/  exec_prepared_stmt (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int expertFinish (TYPE_2__*,int,char**) ; 
 int expertHandleSQL (TYPE_2__*,char const*,char**) ; 
 int /*<<< orphan*/  explain_data_delete (TYPE_2__*) ; 
 int /*<<< orphan*/  explain_data_prepare (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_debug_trace_modes () ; 
 char* save_err_msg (int /*<<< orphan*/ *) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_db_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,char const**) ; 
 char* sqlite3_sql (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int sqlite3_stmt_isexplain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int shell_exec(
  ShellState *pArg,                         /* Pointer to ShellState */
  const char *zSql,                         /* SQL to be evaluated */
  char **pzErrMsg                           /* Error msg written here */
){
  sqlite3_stmt *pStmt = NULL;     /* Statement to execute. */
  int rc = SQLITE_OK;             /* Return Code */
  int rc2;
  const char *zLeftover;          /* Tail of unprocessed SQL */
  sqlite3 *db = pArg->db;

  if( pzErrMsg ){
    *pzErrMsg = NULL;
  }

#ifndef SQLITE_OMIT_VIRTUALTABLE
  if( pArg->expert.pExpert ){
    rc = expertHandleSQL(pArg, zSql, pzErrMsg);
    return expertFinish(pArg, (rc!=SQLITE_OK), pzErrMsg);
  }
#endif

  while( zSql[0] && (SQLITE_OK == rc) ){
    static const char *zStmtSql;
    rc = sqlite3_prepare_v2(db, zSql, -1, &pStmt, &zLeftover);
    if( SQLITE_OK != rc ){
      if( pzErrMsg ){
        *pzErrMsg = save_err_msg(db);
      }
    }else{
      if( !pStmt ){
        /* this happens for a comment or white-space */
        zSql = zLeftover;
        while( IsSpace(zSql[0]) ) zSql++;
        continue;
      }
      zStmtSql = sqlite3_sql(pStmt);
      if( zStmtSql==0 ) zStmtSql = "";
      while( IsSpace(zStmtSql[0]) ) zStmtSql++;

      /* save off the prepared statment handle and reset row count */
      if( pArg ){
        pArg->pStmt = pStmt;
        pArg->cnt = 0;
      }

      /* echo the sql statement if echo on */
      if( pArg && ShellHasFlag(pArg, SHFLG_Echo) ){
        utf8_printf(pArg->out, "%s\n", zStmtSql ? zStmtSql : zSql);
      }

      /* Show the EXPLAIN QUERY PLAN if .eqp is on */
      if( pArg && pArg->autoEQP && sqlite3_stmt_isexplain(pStmt)==0 ){
        sqlite3_stmt *pExplain;
        char *zEQP;
        int triggerEQP = 0;
        disable_debug_trace_modes();
        sqlite3_db_config(db, SQLITE_DBCONFIG_TRIGGER_EQP, -1, &triggerEQP);
        if( pArg->autoEQP>=AUTOEQP_trigger ){
          sqlite3_db_config(db, SQLITE_DBCONFIG_TRIGGER_EQP, 1, 0);
        }
        zEQP = sqlite3_mprintf("EXPLAIN QUERY PLAN %s", zStmtSql);
        rc = sqlite3_prepare_v2(db, zEQP, -1, &pExplain, 0);
        if( rc==SQLITE_OK ){
          while( sqlite3_step(pExplain)==SQLITE_ROW ){
            const char *zEQPLine = (const char*)sqlite3_column_text(pExplain,3);
            int iEqpId = sqlite3_column_int(pExplain, 0);
            int iParentId = sqlite3_column_int(pExplain, 1);
            if( zEQPLine[0]=='-' ) eqp_render(pArg);
            eqp_append(pArg, iEqpId, iParentId, zEQPLine);
          }
          eqp_render(pArg);
        }
        sqlite3_finalize(pExplain);
        sqlite3_free(zEQP);
        if( pArg->autoEQP>=AUTOEQP_full ){
          /* Also do an EXPLAIN for ".eqp full" mode */
          zEQP = sqlite3_mprintf("EXPLAIN %s", zStmtSql);
          rc = sqlite3_prepare_v2(db, zEQP, -1, &pExplain, 0);
          if( rc==SQLITE_OK ){
            pArg->cMode = MODE_Explain;
            explain_data_prepare(pArg, pExplain);
            exec_prepared_stmt(pArg, pExplain);
            explain_data_delete(pArg);
          }
          sqlite3_finalize(pExplain);
          sqlite3_free(zEQP);
        }
        if( pArg->autoEQP>=AUTOEQP_trigger && triggerEQP==0 ){
          sqlite3_db_config(db, SQLITE_DBCONFIG_TRIGGER_EQP, 0, 0);
          /* Reprepare pStmt before reactiving trace modes */
          sqlite3_finalize(pStmt);
          sqlite3_prepare_v2(db, zSql, -1, &pStmt, 0);
          if( pArg ) pArg->pStmt = pStmt;
        }
        restore_debug_trace_modes();
      }

      if( pArg ){
        pArg->cMode = pArg->mode;
        if( pArg->autoExplain ){
          if( sqlite3_stmt_isexplain(pStmt)==1 ){
            pArg->cMode = MODE_Explain;
          }
          if( sqlite3_stmt_isexplain(pStmt)==2 ){
            pArg->cMode = MODE_EQP;
          }
        }

        /* If the shell is currently in ".explain" mode, gather the extra
        ** data required to add indents to the output.*/
        if( pArg->cMode==MODE_Explain ){
          explain_data_prepare(pArg, pStmt);
        }
      }

      bind_prepared_stmt(pArg, pStmt);
      exec_prepared_stmt(pArg, pStmt);
      explain_data_delete(pArg);
      eqp_render(pArg);

      /* print usage stats if stats on */
      if( pArg && pArg->statsOn ){
        display_stats(db, pArg, 0);
      }

      /* print loop-counters if required */
      if( pArg && pArg->scanstatsOn ){
        display_scanstats(db, pArg);
      }

      /* Finalize the statement just executed. If this fails, save a
      ** copy of the error message. Otherwise, set zSql to point to the
      ** next statement to execute. */
      rc2 = sqlite3_finalize(pStmt);
      if( rc!=SQLITE_NOMEM ) rc = rc2;
      if( rc==SQLITE_OK ){
        zSql = zLeftover;
        while( IsSpace(zSql[0]) ) zSql++;
      }else if( pzErrMsg ){
        *pzErrMsg = save_err_msg(db);
      }

      /* clear saved stmt handle */
      if( pArg ){
        pArg->pStmt = NULL;
      }
    }
  } /* end while */

  return rc;
}