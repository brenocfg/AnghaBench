#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3expert ;
struct TYPE_11__ {struct TYPE_11__* pLink; struct TYPE_11__* pNext; } ;
struct TYPE_10__ {TYPE_2__* pRange; TYPE_2__* pEq; } ;
typedef  TYPE_1__ IdxScan ;
typedef  TYPE_2__ IdxConstraint ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int idxCreateFromCons (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  idxFindConstraint (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static int idxCreateFromWhere(
  sqlite3expert *p, 
  IdxScan *pScan,                 /* Create indexes for this scan */
  IdxConstraint *pTail            /* range/ORDER BY constraints for inclusion */
){
  IdxConstraint *p1 = 0;
  IdxConstraint *pCon;
  int rc;

  /* Gather up all the == constraints. */
  for(pCon=pScan->pEq; pCon; pCon=pCon->pNext){
    if( !idxFindConstraint(p1, pCon) && !idxFindConstraint(pTail, pCon) ){
      pCon->pLink = p1;
      p1 = pCon;
    }
  }

  /* Create an index using the == constraints collected above. And the
  ** range constraint/ORDER BY terms passed in by the caller, if any. */
  rc = idxCreateFromCons(p, pScan, p1, pTail);

  /* If no range/ORDER BY passed by the caller, create a version of the
  ** index for each range constraint.  */
  if( pTail==0 ){
    for(pCon=pScan->pRange; rc==SQLITE_OK && pCon; pCon=pCon->pNext){
      assert( pCon->pLink==0 );
      if( !idxFindConstraint(p1, pCon) && !idxFindConstraint(pTail, pCon) ){
        rc = idxCreateFromCons(p, pScan, p1, pCon);
      }
    }
  }

  return rc;
}