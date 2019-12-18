#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
struct TYPE_4__ {int historySize; int* hashBuf; int* btBuf; int /*<<< orphan*/  btSync; int /*<<< orphan*/  hashSync; int /*<<< orphan*/ * MatchFinder; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CMatchFinderMt ;
typedef  int /*<<< orphan*/  CMatchFinder ;

/* Variables and functions */
 int /*<<< orphan*/  BtThreadFunc2 ; 
 int /*<<< orphan*/  HashThreadFunc2 ; 
 scalar_t__ ISzAlloc_Alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MatchFinder_Create (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MtSync_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_ERROR_PARAM ; 
 int /*<<< orphan*/  SZ_OK ; 
 int kBtBufferSize ; 
 int kHashBufferSize ; 
 int kMtBtBlockSize ; 
 int /*<<< orphan*/  kMtBtNumBlocks ; 
 scalar_t__ kMtHashBlockSize ; 
 int /*<<< orphan*/  kMtHashNumBlocks ; 

SRes MatchFinderMt_Create(CMatchFinderMt *p, UInt32 historySize, UInt32 keepAddBufferBefore,
    UInt32 matchMaxLen, UInt32 keepAddBufferAfter, ISzAllocPtr alloc)
{
  CMatchFinder *mf = p->MatchFinder;
  p->historySize = historySize;
  if (kMtBtBlockSize <= matchMaxLen * 4)
    return SZ_ERROR_PARAM;
  if (!p->hashBuf)
  {
    p->hashBuf = (UInt32 *)ISzAlloc_Alloc(alloc, (kHashBufferSize + kBtBufferSize) * sizeof(UInt32));
    if (!p->hashBuf)
      return SZ_ERROR_MEM;
    p->btBuf = p->hashBuf + kHashBufferSize;
  }
  keepAddBufferBefore += (kHashBufferSize + kBtBufferSize);
  keepAddBufferAfter += kMtHashBlockSize;
  if (!MatchFinder_Create(mf, historySize, keepAddBufferBefore, matchMaxLen, keepAddBufferAfter, alloc))
    return SZ_ERROR_MEM;

  RINOK(MtSync_Create(&p->hashSync, HashThreadFunc2, p, kMtHashNumBlocks));
  RINOK(MtSync_Create(&p->btSync, BtThreadFunc2, p, kMtBtNumBlocks));
  return SZ_OK;
}