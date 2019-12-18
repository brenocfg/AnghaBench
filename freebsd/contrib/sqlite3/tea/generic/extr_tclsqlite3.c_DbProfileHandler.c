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
typedef  int /*<<< orphan*/  zTm ;
typedef  int /*<<< orphan*/  sqlite_uint64 ;
typedef  int /*<<< orphan*/  Tcl_DString ;
struct TYPE_2__ {int /*<<< orphan*/  interp; int /*<<< orphan*/  zProfile; } ;
typedef  TYPE_1__ SqliteDb ;

/* Variables and functions */
 int /*<<< orphan*/  Tcl_DStringAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Tcl_DStringAppendElement (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  Tcl_DStringFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_DStringInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_DStringValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_Eval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_ResetResult (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DbProfileHandler(void *cd, const char *zSql, sqlite_uint64 tm){
  SqliteDb *pDb = (SqliteDb*)cd;
  Tcl_DString str;
  char zTm[100];

  sqlite3_snprintf(sizeof(zTm)-1, zTm, "%lld", tm);
  Tcl_DStringInit(&str);
  Tcl_DStringAppend(&str, pDb->zProfile, -1);
  Tcl_DStringAppendElement(&str, zSql);
  Tcl_DStringAppendElement(&str, zTm);
  Tcl_Eval(pDb->interp, Tcl_DStringValue(&str));
  Tcl_DStringFree(&str);
  Tcl_ResetResult(pDb->interp);
}