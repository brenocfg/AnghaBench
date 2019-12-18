#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ i16 ;
struct TYPE_7__ {int szEst; } ;
struct TYPE_6__ {int nColumn; scalar_t__* aiColumn; int /*<<< orphan*/  szIdxRow; TYPE_1__* pTable; } ;
struct TYPE_5__ {scalar_t__ nCol; TYPE_3__* aCol; } ;
typedef  TYPE_2__ Index ;
typedef  TYPE_3__ Column ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3LogEst (unsigned int) ; 

__attribute__((used)) static void estimateIndexWidth(Index *pIdx){
  unsigned wIndex = 0;
  int i;
  const Column *aCol = pIdx->pTable->aCol;
  for(i=0; i<pIdx->nColumn; i++){
    i16 x = pIdx->aiColumn[i];
    assert( x<pIdx->pTable->nCol );
    wIndex += x<0 ? 1 : aCol[pIdx->aiColumn[i]].szEst;
  }
  pIdx->szIdxRow = sqlite3LogEst(wIndex*4);
}