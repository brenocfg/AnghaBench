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
struct SrcList_item {TYPE_4__* pSelect; TYPE_2__* pTab; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pParse; } ;
typedef  TYPE_1__ Walker ;
struct TYPE_10__ {int tabFlags; } ;
typedef  TYPE_2__ Table ;
struct TYPE_12__ {int selFlags; struct TYPE_12__* pPrior; TYPE_3__* pSrc; } ;
struct TYPE_11__ {int nSrc; struct SrcList_item* a; } ;
typedef  TYPE_3__ SrcList ;
typedef  TYPE_4__ Select ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int SF_HasTypeInfo ; 
 int SF_Resolved ; 
 int /*<<< orphan*/  SQLITE_AFF_NONE ; 
 int TF_Ephemeral ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3SelectAddColumnTypeAndCollation (int /*<<< orphan*/ *,TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void selectAddSubqueryTypeInfo(Walker *pWalker, Select *p){
  Parse *pParse;
  int i;
  SrcList *pTabList;
  struct SrcList_item *pFrom;

  assert( p->selFlags & SF_Resolved );
  if( p->selFlags & SF_HasTypeInfo ) return;
  p->selFlags |= SF_HasTypeInfo;
  pParse = pWalker->pParse;
  pTabList = p->pSrc;
  for(i=0, pFrom=pTabList->a; i<pTabList->nSrc; i++, pFrom++){
    Table *pTab = pFrom->pTab;
    assert( pTab!=0 );
    if( (pTab->tabFlags & TF_Ephemeral)!=0 ){
      /* A sub-query in the FROM clause of a SELECT */
      Select *pSel = pFrom->pSelect;
      if( pSel ){
        while( pSel->pPrior ) pSel = pSel->pPrior;
        sqlite3SelectAddColumnTypeAndCollation(pParse, pTab, pSel,
                                               SQLITE_AFF_NONE);
      }
    }
  }
}