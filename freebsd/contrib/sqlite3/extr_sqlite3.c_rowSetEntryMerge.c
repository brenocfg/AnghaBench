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
struct RowSetEntry {scalar_t__ v; struct RowSetEntry* pRight; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static struct RowSetEntry *rowSetEntryMerge(
  struct RowSetEntry *pA,    /* First sorted list to be merged */
  struct RowSetEntry *pB     /* Second sorted list to be merged */
){
  struct RowSetEntry head;
  struct RowSetEntry *pTail;

  pTail = &head;
  assert( pA!=0 && pB!=0 );
  for(;;){
    assert( pA->pRight==0 || pA->v<=pA->pRight->v );
    assert( pB->pRight==0 || pB->v<=pB->pRight->v );
    if( pA->v<=pB->v ){
      if( pA->v<pB->v ) pTail = pTail->pRight = pA;
      pA = pA->pRight;
      if( pA==0 ){
        pTail->pRight = pB;
        break;
      }
    }else{
      pTail = pTail->pRight = pB;
      pB = pB->pRight;
      if( pB==0 ){
        pTail->pRight = pA;
        break;
      }
    }
  }
  return head.pRight;
}