#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  cutValue; int /*<<< orphan*/  cyclicBufferSize; int /*<<< orphan*/  cyclicBufferPos; int /*<<< orphan*/  buffer; int /*<<< orphan*/  pos; int /*<<< orphan*/  numHashBytes; int /*<<< orphan*/  matchMaxLen; int /*<<< orphan*/  son; int /*<<< orphan*/  crc; int /*<<< orphan*/  fixedHashSize; int /*<<< orphan*/  hash; } ;
struct TYPE_7__ {int /*<<< orphan*/  cutValue; int /*<<< orphan*/  cyclicBufferSize; int /*<<< orphan*/  cyclicBufferPos; int /*<<< orphan*/  buffer; int /*<<< orphan*/  pos; int /*<<< orphan*/  numHashBytes; int /*<<< orphan*/  matchMaxLen; int /*<<< orphan*/  son; int /*<<< orphan*/  crc; int /*<<< orphan*/  fixedHashSize; int /*<<< orphan*/  hash; scalar_t__ historySize; scalar_t__ lzPos; scalar_t__ btNumAvailBytes; int /*<<< orphan*/  pointerToCurPos; scalar_t__ hashBufPosLimit; scalar_t__ hashBufPos; scalar_t__ btBufPosLimit; scalar_t__ btBufPos; TYPE_2__* MatchFinder; } ;
typedef  TYPE_1__ CMatchFinderMt ;
typedef  TYPE_2__ CMatchFinder ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  Inline_MatchFinder_GetPointerToCurrentPos (TYPE_2__*) ; 
 int /*<<< orphan*/  MatchFinder_Init_3 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MatchFinder_Init_LowHash (TYPE_2__*) ; 

__attribute__((used)) static void MatchFinderMt_Init(CMatchFinderMt *p)
{
  CMatchFinder *mf = p->MatchFinder;
  
  p->btBufPos =
  p->btBufPosLimit = 0;
  p->hashBufPos =
  p->hashBufPosLimit = 0;

  /* Init without data reading. We don't want to read data in this thread */
  MatchFinder_Init_3(mf, False);
  MatchFinder_Init_LowHash(mf);
  
  p->pointerToCurPos = Inline_MatchFinder_GetPointerToCurrentPos(mf);
  p->btNumAvailBytes = 0;
  p->lzPos = p->historySize + 1;

  p->hash = mf->hash;
  p->fixedHashSize = mf->fixedHashSize;
  p->crc = mf->crc;

  p->son = mf->son;
  p->matchMaxLen = mf->matchMaxLen;
  p->numHashBytes = mf->numHashBytes;
  p->pos = mf->pos;
  p->buffer = mf->buffer;
  p->cyclicBufferPos = mf->cyclicBufferPos;
  p->cyclicBufferSize = mf->cyclicBufferSize;
  p->cutValue = mf->cutValue;
}