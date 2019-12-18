#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  Tcl_Obj ;
struct TYPE_2__ {int pUpdateHook; int /*<<< orphan*/  interp; } ;
typedef  TYPE_1__ SqliteDb ;

/* Variables and functions */
 int SQLITE_DELETE ; 
 int SQLITE_INSERT ; 
 int SQLITE_UPDATE ; 
 int /*<<< orphan*/  TCL_EVAL_DIRECT ; 
 int /*<<< orphan*/  Tcl_DecrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Tcl_DuplicateObj (int) ; 
 int /*<<< orphan*/  Tcl_EvalObjEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_IncrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_ListObjAppendElement (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_NewStringObj (char const*,int) ; 
 int /*<<< orphan*/  Tcl_NewWideIntObj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void DbUpdateHandler(
  void *p,
  int op,
  const char *zDb,
  const char *zTbl,
  sqlite_int64 rowid
){
  SqliteDb *pDb = (SqliteDb *)p;
  Tcl_Obj *pCmd;
  static const char *azStr[] = {"DELETE", "INSERT", "UPDATE"};

  assert( (SQLITE_DELETE-1)/9 == 0 );
  assert( (SQLITE_INSERT-1)/9 == 1 );
  assert( (SQLITE_UPDATE-1)/9 == 2 );

  assert( pDb->pUpdateHook );
  assert( op==SQLITE_INSERT || op==SQLITE_UPDATE || op==SQLITE_DELETE );

  pCmd = Tcl_DuplicateObj(pDb->pUpdateHook);
  Tcl_IncrRefCount(pCmd);
  Tcl_ListObjAppendElement(0, pCmd, Tcl_NewStringObj(azStr[(op-1)/9], -1));
  Tcl_ListObjAppendElement(0, pCmd, Tcl_NewStringObj(zDb, -1));
  Tcl_ListObjAppendElement(0, pCmd, Tcl_NewStringObj(zTbl, -1));
  Tcl_ListObjAppendElement(0, pCmd, Tcl_NewWideIntObj(rowid));
  Tcl_EvalObjEx(pDb->interp, pCmd, TCL_EVAL_DIRECT);
  Tcl_DecrRefCount(pCmd);
}