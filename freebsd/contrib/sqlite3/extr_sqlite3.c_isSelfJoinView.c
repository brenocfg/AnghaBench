#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ viaCoroutine; } ;
struct SrcList_item {scalar_t__ zName; TYPE_4__* pSelect; TYPE_2__* pTab; TYPE_1__ fg; } ;
struct TYPE_9__ {scalar_t__ selId; int /*<<< orphan*/  pHaving; int /*<<< orphan*/  pWhere; } ;
struct TYPE_8__ {struct SrcList_item* a; } ;
struct TYPE_7__ {scalar_t__ pSchema; } ;
typedef  TYPE_3__ SrcList ;
typedef  TYPE_4__ Select ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3ExprCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_stricmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct SrcList_item *isSelfJoinView(
  SrcList *pTabList,           /* Search for self-joins in this FROM clause */
  struct SrcList_item *pThis   /* Search for prior reference to this subquery */
){
  struct SrcList_item *pItem;
  for(pItem = pTabList->a; pItem<pThis; pItem++){
    Select *pS1;
    if( pItem->pSelect==0 ) continue;
    if( pItem->fg.viaCoroutine ) continue;
    if( pItem->zName==0 ) continue;
    assert( pItem->pTab!=0 );
    assert( pThis->pTab!=0 );
    if( pItem->pTab->pSchema!=pThis->pTab->pSchema ) continue;
    if( sqlite3_stricmp(pItem->zName, pThis->zName)!=0 ) continue;
    pS1 = pItem->pSelect;
    if( pItem->pTab->pSchema==0 && pThis->pSelect->selId!=pS1->selId ){
      /* The query flattener left two different CTE tables with identical
      ** names in the same FROM clause. */
      continue;
    }
    if( sqlite3ExprCompare(0, pThis->pSelect->pWhere, pS1->pWhere, -1)
     || sqlite3ExprCompare(0, pThis->pSelect->pHaving, pS1->pHaving, -1) 
    ){
      /* The view was modified by some other optimization such as
      ** pushDownWhereTerms() */
      continue;
    }
    return pItem;
  }
  return 0;
}