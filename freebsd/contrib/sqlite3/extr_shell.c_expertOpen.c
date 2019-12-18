#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  ExpertCsr ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/ * idxMalloc (int*,int) ; 

__attribute__((used)) static int expertOpen(sqlite3_vtab *pVTab, sqlite3_vtab_cursor **ppCursor){
  int rc = SQLITE_OK;
  ExpertCsr *pCsr;
  (void)pVTab;
  pCsr = idxMalloc(&rc, sizeof(ExpertCsr));
  *ppCursor = (sqlite3_vtab_cursor*)pCsr;
  return rc;
}