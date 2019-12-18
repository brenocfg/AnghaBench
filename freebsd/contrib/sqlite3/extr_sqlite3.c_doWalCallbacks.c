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
struct TYPE_6__ {int nDb; int (* xWalCallback ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ;TYPE_1__* aDb; int /*<<< orphan*/  pWalArg; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_5__ {int /*<<< orphan*/  zDbSName; int /*<<< orphan*/ * pBt; } ;
typedef  int /*<<< orphan*/  Btree ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3BtreePager (int /*<<< orphan*/ *) ; 
 int sqlite3PagerWalCallback (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int doWalCallbacks(sqlite3 *db){
  int rc = SQLITE_OK;
#ifndef SQLITE_OMIT_WAL
  int i;
  for(i=0; i<db->nDb; i++){
    Btree *pBt = db->aDb[i].pBt;
    if( pBt ){
      int nEntry;
      sqlite3BtreeEnter(pBt);
      nEntry = sqlite3PagerWalCallback(sqlite3BtreePager(pBt));
      sqlite3BtreeLeave(pBt);
      if( nEntry>0 && db->xWalCallback && rc==SQLITE_OK ){
        rc = db->xWalCallback(db->pWalArg, db, db->aDb[i].zDbSName, nEntry);
      }
    }
  }
#endif
  return rc;
}