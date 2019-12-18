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
typedef  int u8 ;
struct TYPE_6__ {int /*<<< orphan*/  max1bytePayload; int /*<<< orphan*/  minLocal; int /*<<< orphan*/  maxLocal; int /*<<< orphan*/  minLeaf; int /*<<< orphan*/  maxLeaf; int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {int hdrOffset; int pgno; int leaf; int childPtrSize; int intKey; int intKeyLeaf; int /*<<< orphan*/  max1bytePayload; int /*<<< orphan*/  minLocal; int /*<<< orphan*/  maxLocal; int /*<<< orphan*/  xParseCell; int /*<<< orphan*/  xCellSize; TYPE_2__* pBt; } ;
typedef  TYPE_1__ MemPage ;
typedef  TYPE_2__ BtShared ;

/* Variables and functions */
 int PTF_INTKEY ; 
 int PTF_LEAF ; 
 int PTF_LEAFDATA ; 
 int PTF_ZERODATA ; 
 int SQLITE_CORRUPT_PAGE (TYPE_1__*) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  btreeParseCellPtr ; 
 int /*<<< orphan*/  btreeParseCellPtrIndex ; 
 int /*<<< orphan*/  btreeParseCellPtrNoPayload ; 
 int /*<<< orphan*/  cellSizePtr ; 
 int /*<<< orphan*/  cellSizePtrNoPayload ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decodeFlags(MemPage *pPage, int flagByte){
  BtShared *pBt;     /* A copy of pPage->pBt */

  assert( pPage->hdrOffset==(pPage->pgno==1 ? 100 : 0) );
  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  pPage->leaf = (u8)(flagByte>>3);  assert( PTF_LEAF == 1<<3 );
  flagByte &= ~PTF_LEAF;
  pPage->childPtrSize = 4-4*pPage->leaf;
  pPage->xCellSize = cellSizePtr;
  pBt = pPage->pBt;
  if( flagByte==(PTF_LEAFDATA | PTF_INTKEY) ){
    /* EVIDENCE-OF: R-07291-35328 A value of 5 (0x05) means the page is an
    ** interior table b-tree page. */
    assert( (PTF_LEAFDATA|PTF_INTKEY)==5 );
    /* EVIDENCE-OF: R-26900-09176 A value of 13 (0x0d) means the page is a
    ** leaf table b-tree page. */
    assert( (PTF_LEAFDATA|PTF_INTKEY|PTF_LEAF)==13 );
    pPage->intKey = 1;
    if( pPage->leaf ){
      pPage->intKeyLeaf = 1;
      pPage->xParseCell = btreeParseCellPtr;
    }else{
      pPage->intKeyLeaf = 0;
      pPage->xCellSize = cellSizePtrNoPayload;
      pPage->xParseCell = btreeParseCellPtrNoPayload;
    }
    pPage->maxLocal = pBt->maxLeaf;
    pPage->minLocal = pBt->minLeaf;
  }else if( flagByte==PTF_ZERODATA ){
    /* EVIDENCE-OF: R-43316-37308 A value of 2 (0x02) means the page is an
    ** interior index b-tree page. */
    assert( (PTF_ZERODATA)==2 );
    /* EVIDENCE-OF: R-59615-42828 A value of 10 (0x0a) means the page is a
    ** leaf index b-tree page. */
    assert( (PTF_ZERODATA|PTF_LEAF)==10 );
    pPage->intKey = 0;
    pPage->intKeyLeaf = 0;
    pPage->xParseCell = btreeParseCellPtrIndex;
    pPage->maxLocal = pBt->maxLocal;
    pPage->minLocal = pBt->minLocal;
  }else{
    /* EVIDENCE-OF: R-47608-56469 Any other value for the b-tree page type is
    ** an error. */
    return SQLITE_CORRUPT_PAGE(pPage);
  }
  pPage->max1bytePayload = pBt->max1bytePayload;
  return SQLITE_OK;
}