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
typedef  int /*<<< orphan*/  sqlite3_pcache ;
struct TYPE_7__ {int nMax; int n90pct; TYPE_1__* pGroup; scalar_t__ bPurgeable; } ;
struct TYPE_6__ {int nMaxPage; int mxPinned; int nMinPage; } ;
typedef  TYPE_1__ PGroup ;
typedef  TYPE_2__ PCache1 ;

/* Variables and functions */
 int /*<<< orphan*/  pcache1EnforceMaxPage (TYPE_2__*) ; 
 int /*<<< orphan*/  pcache1EnterMutex (TYPE_1__*) ; 
 int /*<<< orphan*/  pcache1LeaveMutex (TYPE_1__*) ; 

__attribute__((used)) static void pcache1Cachesize(sqlite3_pcache *p, int nMax){
  PCache1 *pCache = (PCache1 *)p;
  if( pCache->bPurgeable ){
    PGroup *pGroup = pCache->pGroup;
    pcache1EnterMutex(pGroup);
    pGroup->nMaxPage += (nMax - pCache->nMax);
    pGroup->mxPinned = pGroup->nMaxPage + 10 - pGroup->nMinPage;
    pCache->nMax = nMax;
    pCache->n90pct = pCache->nMax*9/10;
    pcache1EnforceMaxPage(pCache);
    pcache1LeaveMutex(pGroup);
  }
}