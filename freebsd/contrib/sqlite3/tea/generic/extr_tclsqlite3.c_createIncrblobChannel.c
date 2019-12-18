#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zChannel ;
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_blob ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  Tcl_Interp ;
struct TYPE_6__ {int /*<<< orphan*/  channel; TYPE_1__* pDb; struct TYPE_6__* pPrev; struct TYPE_6__* pNext; int /*<<< orphan*/ * pBlob; scalar_t__ iSeek; } ;
struct TYPE_5__ {TYPE_2__* pIncrblob; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ SqliteDb ;
typedef  TYPE_2__ IncrblobChannel ;

/* Variables and functions */
 int /*<<< orphan*/  IncrblobChannelType ; 
 int SQLITE_OK ; 
 int TCL_ERROR ; 
 int TCL_OK ; 
 int TCL_READABLE ; 
 int /*<<< orphan*/  TCL_VOLATILE ; 
 int TCL_WRITABLE ; 
 scalar_t__ Tcl_Alloc (int) ; 
 int /*<<< orphan*/  Tcl_CreateChannel (int /*<<< orphan*/ *,char*,TYPE_2__*,int) ; 
 scalar_t__ Tcl_GetChannelName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_RegisterChannel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_SetResult (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int sqlite3_blob_open (int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 scalar_t__ sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int) ; 

__attribute__((used)) static int createIncrblobChannel(
  Tcl_Interp *interp,
  SqliteDb *pDb,
  const char *zDb,
  const char *zTable,
  const char *zColumn,
  sqlite_int64 iRow,
  int isReadonly
){
  IncrblobChannel *p;
  sqlite3 *db = pDb->db;
  sqlite3_blob *pBlob;
  int rc;
  int flags = TCL_READABLE|(isReadonly ? 0 : TCL_WRITABLE);

  /* This variable is used to name the channels: "incrblob_[incr count]" */
  static int count = 0;
  char zChannel[64];

  rc = sqlite3_blob_open(db, zDb, zTable, zColumn, iRow, !isReadonly, &pBlob);
  if( rc!=SQLITE_OK ){
    Tcl_SetResult(interp, (char *)sqlite3_errmsg(pDb->db), TCL_VOLATILE);
    return TCL_ERROR;
  }

  p = (IncrblobChannel *)Tcl_Alloc(sizeof(IncrblobChannel));
  p->iSeek = 0;
  p->pBlob = pBlob;

  sqlite3_snprintf(sizeof(zChannel), zChannel, "incrblob_%d", ++count);
  p->channel = Tcl_CreateChannel(&IncrblobChannelType, zChannel, p, flags);
  Tcl_RegisterChannel(interp, p->channel);

  /* Link the new channel into the SqliteDb.pIncrblob list. */
  p->pNext = pDb->pIncrblob;
  p->pPrev = 0;
  if( p->pNext ){
    p->pNext->pPrev = p;
  }
  pDb->pIncrblob = p;
  p->pDb = pDb;

  Tcl_SetResult(interp, (char *)Tcl_GetChannelName(p->channel), TCL_VOLATILE);
  return TCL_OK;
}