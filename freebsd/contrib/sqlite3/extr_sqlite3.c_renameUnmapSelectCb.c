#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * pParse; } ;
typedef  TYPE_2__ Walker ;
struct TYPE_12__ {TYPE_3__* pSrc; TYPE_3__* pEList; } ;
struct TYPE_11__ {int nExpr; int nSrc; TYPE_1__* a; } ;
struct TYPE_9__ {scalar_t__ zName; } ;
typedef  TYPE_3__ SrcList ;
typedef  TYPE_4__ Select ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_3__ ExprList ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_3__*) ; 
 int WRC_Continue ; 
 int /*<<< orphan*/  sqlite3RenameTokenRemap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int renameUnmapSelectCb(Walker *pWalker, Select *p){
  Parse *pParse = pWalker->pParse;
  int i;
  if( ALWAYS(p->pEList) ){
    ExprList *pList = p->pEList;
    for(i=0; i<pList->nExpr; i++){
      if( pList->a[i].zName ){
        sqlite3RenameTokenRemap(pParse, 0, (void*)pList->a[i].zName);
      }
    }
  }
  if( ALWAYS(p->pSrc) ){  /* Every Select as a SrcList, even if it is empty */
    SrcList *pSrc = p->pSrc;
    for(i=0; i<pSrc->nSrc; i++){
      sqlite3RenameTokenRemap(pParse, 0, (void*)pSrc->a[i].zName);
    }
  }
  return WRC_Continue;
}