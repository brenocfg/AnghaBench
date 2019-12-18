#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  aModule; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_7__ {int /*<<< orphan*/  zName; } ;
typedef  TYPE_2__ Module ;
typedef  int /*<<< orphan*/  HashElem ;

/* Variables and functions */
 int SQLITE_MISUSE_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  createModule (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SafetyCheckOk (TYPE_1__*) ; 
 scalar_t__ sqliteHashData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashFirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashNext (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int sqlite3_drop_modules(sqlite3 *db, const char** azNames){
  HashElem *pThis, *pNext;
#ifdef SQLITE_ENABLE_API_ARMOR
  if( !sqlite3SafetyCheckOk(db) ) return SQLITE_MISUSE_BKPT;
#endif
  for(pThis=sqliteHashFirst(&db->aModule); pThis; pThis=pNext){
    Module *pMod = (Module*)sqliteHashData(pThis);
    pNext = sqliteHashNext(pThis);
    if( azNames ){
      int ii;
      for(ii=0; azNames[ii]!=0 && strcmp(azNames[ii],pMod->zName)!=0; ii++){}
      if( azNames[ii]!=0 ) continue;
    }
    createModule(db, pMod->zName, 0, 0, 0);
  }
  return SQLITE_OK;
}