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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_4__ {scalar_t__ cMode; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 scalar_t__ MODE_Insert ; 
 int SQLITE_ABORT ; 
 int SQLITE_BLOB ; 
 int SQLITE_NOMEM ; 
 int SQLITE_NULL ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ shell_callback (TYPE_1__*,int,char**,char**,int*) ; 
 int sqlite3_column_count (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_column_name (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_free (void*) ; 
 void* sqlite3_malloc64 (int) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void exec_prepared_stmt(
  ShellState *pArg,                                /* Pointer to ShellState */
  sqlite3_stmt *pStmt                              /* Statment to run */
){
  int rc;

  /* perform the first step.  this will tell us if we
  ** have a result set or not and how wide it is.
  */
  rc = sqlite3_step(pStmt);
  /* if we have a result set... */
  if( SQLITE_ROW == rc ){
    /* allocate space for col name ptr, value ptr, and type */
    int nCol = sqlite3_column_count(pStmt);
    void *pData = sqlite3_malloc64(3*nCol*sizeof(const char*) + 1);
    if( !pData ){
      rc = SQLITE_NOMEM;
    }else{
      char **azCols = (char **)pData;      /* Names of result columns */
      char **azVals = &azCols[nCol];       /* Results */
      int *aiTypes = (int *)&azVals[nCol]; /* Result types */
      int i, x;
      assert(sizeof(int) <= sizeof(char *));
      /* save off ptrs to column names */
      for(i=0; i<nCol; i++){
        azCols[i] = (char *)sqlite3_column_name(pStmt, i);
      }
      do{
        /* extract the data and data types */
        for(i=0; i<nCol; i++){
          aiTypes[i] = x = sqlite3_column_type(pStmt, i);
          if( x==SQLITE_BLOB && pArg && pArg->cMode==MODE_Insert ){
            azVals[i] = "";
          }else{
            azVals[i] = (char*)sqlite3_column_text(pStmt, i);
          }
          if( !azVals[i] && (aiTypes[i]!=SQLITE_NULL) ){
            rc = SQLITE_NOMEM;
            break; /* from for */
          }
        } /* end for */

        /* if data and types extracted successfully... */
        if( SQLITE_ROW == rc ){
          /* call the supplied callback with the result row data */
          if( shell_callback(pArg, nCol, azVals, azCols, aiTypes) ){
            rc = SQLITE_ABORT;
          }else{
            rc = sqlite3_step(pStmt);
          }
        }
      } while( SQLITE_ROW == rc );
      sqlite3_free(pData);
    }
  }
}