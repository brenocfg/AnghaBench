#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;
struct TYPE_7__ {int nCol; int /*<<< orphan*/ ** apColName; scalar_t__ pArray; TYPE_2__* pDb; TYPE_1__* pPreStmt; } ;
struct TYPE_6__ {int /*<<< orphan*/ * interp; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pStmt; } ;
typedef  TYPE_3__ DbEvalContext ;

/* Variables and functions */
 scalar_t__ Tcl_Alloc (int) ; 
 int /*<<< orphan*/  Tcl_DecrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_IncrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_ListObjAppendElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Tcl_NewObj () ; 
 int /*<<< orphan*/ * Tcl_NewStringObj (char*,int) ; 
 int /*<<< orphan*/  Tcl_ObjSetVar2 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_column_count (int /*<<< orphan*/ *) ; 
 char* sqlite3_column_name (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void dbEvalRowInfo(
  DbEvalContext *p,               /* Evaluation context */
  int *pnCol,                     /* OUT: Number of column names */
  Tcl_Obj ***papColName           /* OUT: Array of column names */
){
  /* Compute column names */
  if( 0==p->apColName ){
    sqlite3_stmt *pStmt = p->pPreStmt->pStmt;
    int i;                        /* Iterator variable */
    int nCol;                     /* Number of columns returned by pStmt */
    Tcl_Obj **apColName = 0;      /* Array of column names */

    p->nCol = nCol = sqlite3_column_count(pStmt);
    if( nCol>0 && (papColName || p->pArray) ){
      apColName = (Tcl_Obj**)Tcl_Alloc( sizeof(Tcl_Obj*)*nCol );
      for(i=0; i<nCol; i++){
        apColName[i] = Tcl_NewStringObj(sqlite3_column_name(pStmt,i), -1);
        Tcl_IncrRefCount(apColName[i]);
      }
      p->apColName = apColName;
    }

    /* If results are being stored in an array variable, then create
    ** the array(*) entry for that array
    */
    if( p->pArray ){
      Tcl_Interp *interp = p->pDb->interp;
      Tcl_Obj *pColList = Tcl_NewObj();
      Tcl_Obj *pStar = Tcl_NewStringObj("*", -1);

      for(i=0; i<nCol; i++){
        Tcl_ListObjAppendElement(interp, pColList, apColName[i]);
      }
      Tcl_IncrRefCount(pStar);
      Tcl_ObjSetVar2(interp, p->pArray, pStar, pColList, 0);
      Tcl_DecrRefCount(pStar);
    }
  }

  if( papColName ){
    *papColName = p->apColName;
  }
  if( pnCol ){
    *pnCol = p->nCol;
  }
}