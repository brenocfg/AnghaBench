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
struct TYPE_6__ {TYPE_1__* pMmapFreelist; } ;
struct TYPE_5__ {struct TYPE_5__* pDirty; } ;
typedef  TYPE_1__ PgHdr ;
typedef  TYPE_2__ Pager ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static void pagerFreeMapHdrs(Pager *pPager){
  PgHdr *p;
  PgHdr *pNext;
  for(p=pPager->pMmapFreelist; p; p=pNext){
    pNext = p->pDirty;
    sqlite3_free(p);
  }
}