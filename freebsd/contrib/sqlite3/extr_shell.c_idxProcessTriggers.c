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
struct TYPE_6__ {TYPE_2__* pWrite; } ;
typedef  TYPE_1__ sqlite3expert ;
struct TYPE_7__ {struct TYPE_7__* pNext; } ;
typedef  TYPE_2__ IdxWrite ;

/* Variables and functions */
 int SQLITE_OK ; 
 int idxProcessOneTrigger (TYPE_1__*,TYPE_2__*,char**) ; 

__attribute__((used)) static int idxProcessTriggers(sqlite3expert *p, char **pzErr){
  int rc = SQLITE_OK;
  IdxWrite *pEnd = 0;
  IdxWrite *pFirst = p->pWrite;

  while( rc==SQLITE_OK && pFirst!=pEnd ){
    IdxWrite *pIter;
    for(pIter=pFirst; rc==SQLITE_OK && pIter!=pEnd; pIter=pIter->pNext){
      rc = idxProcessOneTrigger(p, pIter, pzErr);
    }
    pEnd = pFirst;
    pFirst = p->pWrite;
  }

  return rc;
}