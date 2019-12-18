#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int ptrdiff_t ;
typedef  int UInt32 ;
struct TYPE_15__ {scalar_t__ pos; int historySize; int streamPos; int numHashBytes; int buffer; int /*<<< orphan*/  crc; scalar_t__ hashMask; scalar_t__ fixedHashSize; scalar_t__ hash; } ;
struct TYPE_13__ {int numProcessedBlocks; int /*<<< orphan*/  filledSemaphore; int /*<<< orphan*/  freeSemaphore; int /*<<< orphan*/  cs; int /*<<< orphan*/  wasStopped; scalar_t__ stopWriting; scalar_t__ exit; int /*<<< orphan*/  wasStarted; int /*<<< orphan*/  canStart; } ;
struct TYPE_12__ {int /*<<< orphan*/  cs; } ;
struct TYPE_14__ {int pointerToCurPos; int buffer; int* hashBuf; int /*<<< orphan*/  (* GetHeadsFunc ) (int,int,scalar_t__,scalar_t__,int*,int,int /*<<< orphan*/ ) ;TYPE_2__ hashSync; TYPE_1__ btSync; TYPE_4__* MatchFinder; } ;
typedef  TYPE_2__ CMtSync ;
typedef  TYPE_3__ CMatchFinderMt ;
typedef  TYPE_4__ CMatchFinder ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  CriticalSection_Enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CriticalSection_Leave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Event_Set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Event_Wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* Inline_MatchFinder_GetPointerToCurrentPos (TYPE_4__*) ; 
 int /*<<< orphan*/  MatchFinder_Init_HighHash (TYPE_4__*) ; 
 int /*<<< orphan*/  MatchFinder_MoveBlock (TYPE_4__*) ; 
 scalar_t__ MatchFinder_NeedMove (TYPE_4__*) ; 
 int /*<<< orphan*/  MatchFinder_Normalize3 (int,scalar_t__,size_t) ; 
 int /*<<< orphan*/  MatchFinder_ReadIfRequired (TYPE_4__*) ; 
 int /*<<< orphan*/  MatchFinder_ReduceOffsets (TYPE_4__*,int) ; 
 int /*<<< orphan*/  Semaphore_Release1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Semaphore_Wait (int /*<<< orphan*/ *) ; 
 int kMtHashBlockSize ; 
 int kMtHashNumBlocksMask ; 
 scalar_t__ kMtMaxValForNormalize ; 
 int /*<<< orphan*/  stub1 (int,int,scalar_t__,scalar_t__,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void HashThreadFunc(CMatchFinderMt *mt)
{
  CMtSync *p = &mt->hashSync;
  for (;;)
  {
    UInt32 numProcessedBlocks = 0;
    Event_Wait(&p->canStart);
    Event_Set(&p->wasStarted);

    MatchFinder_Init_HighHash(mt->MatchFinder);

    for (;;)
    {
      if (p->exit)
        return;
      if (p->stopWriting)
      {
        p->numProcessedBlocks = numProcessedBlocks;
        Event_Set(&p->wasStopped);
        break;
      }

      {
        CMatchFinder *mf = mt->MatchFinder;
        if (MatchFinder_NeedMove(mf))
        {
          CriticalSection_Enter(&mt->btSync.cs);
          CriticalSection_Enter(&mt->hashSync.cs);
          {
            const Byte *beforePtr = Inline_MatchFinder_GetPointerToCurrentPos(mf);
            ptrdiff_t offset;
            MatchFinder_MoveBlock(mf);
            offset = beforePtr - Inline_MatchFinder_GetPointerToCurrentPos(mf);
            mt->pointerToCurPos -= offset;
            mt->buffer -= offset;
          }
          CriticalSection_Leave(&mt->btSync.cs);
          CriticalSection_Leave(&mt->hashSync.cs);
          continue;
        }

        Semaphore_Wait(&p->freeSemaphore);

        MatchFinder_ReadIfRequired(mf);
        if (mf->pos > (kMtMaxValForNormalize - kMtHashBlockSize))
        {
          UInt32 subValue = (mf->pos - mf->historySize - 1);
          MatchFinder_ReduceOffsets(mf, subValue);
          MatchFinder_Normalize3(subValue, mf->hash + mf->fixedHashSize, (size_t)mf->hashMask + 1);
        }
        {
          UInt32 *heads = mt->hashBuf + ((numProcessedBlocks++) & kMtHashNumBlocksMask) * kMtHashBlockSize;
          UInt32 num = mf->streamPos - mf->pos;
          heads[0] = 2;
          heads[1] = num;
          if (num >= mf->numHashBytes)
          {
            num = num - mf->numHashBytes + 1;
            if (num > kMtHashBlockSize - 2)
              num = kMtHashBlockSize - 2;
            mt->GetHeadsFunc(mf->buffer, mf->pos, mf->hash + mf->fixedHashSize, mf->hashMask, heads + 2, num, mf->crc);
            heads[0] = 2 + num;
          }
          mf->pos += num;
          mf->buffer += num;
        }
      }

      Semaphore_Release1(&p->filledSemaphore);
    }
  }
}