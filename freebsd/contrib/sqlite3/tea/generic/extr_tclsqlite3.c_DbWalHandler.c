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
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;
struct TYPE_2__ {int pWalHook; int /*<<< orphan*/ * db; int /*<<< orphan*/ * interp; } ;
typedef  TYPE_1__ SqliteDb ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ TCL_OK ; 
 int /*<<< orphan*/  Tcl_BackgroundError (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_DecrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Tcl_DuplicateObj (int) ; 
 scalar_t__ Tcl_EvalObjEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ Tcl_GetIntFromObj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  Tcl_GetObjResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_IncrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_ListObjAppendElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_NewIntObj (int) ; 
 int /*<<< orphan*/  Tcl_NewStringObj (char const*,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int DbWalHandler(
  void *clientData,
  sqlite3 *db,
  const char *zDb,
  int nEntry
){
  int ret = SQLITE_OK;
  Tcl_Obj *p;
  SqliteDb *pDb = (SqliteDb*)clientData;
  Tcl_Interp *interp = pDb->interp;
  assert(pDb->pWalHook);

  assert( db==pDb->db );
  p = Tcl_DuplicateObj(pDb->pWalHook);
  Tcl_IncrRefCount(p);
  Tcl_ListObjAppendElement(interp, p, Tcl_NewStringObj(zDb, -1));
  Tcl_ListObjAppendElement(interp, p, Tcl_NewIntObj(nEntry));
  if( TCL_OK!=Tcl_EvalObjEx(interp, p, 0)
   || TCL_OK!=Tcl_GetIntFromObj(interp, Tcl_GetObjResult(interp), &ret)
  ){
    Tcl_BackgroundError(interp);
  }
  Tcl_DecrRefCount(p);

  return ret;
}