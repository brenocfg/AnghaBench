#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numProcessedBlocks; } ;
struct TYPE_4__ {int hashBufPosLimit; int hashBufPos; scalar_t__* hashBuf; scalar_t__ hashNumAvail; TYPE_2__ hashSync; } ;
typedef  TYPE_1__ CMatchFinderMt ;

/* Variables and functions */
 int /*<<< orphan*/  MtSync_GetNextBlock (TYPE_2__*) ; 
 int kMtHashBlockSize ; 
 int kMtHashNumBlocksMask ; 

__attribute__((used)) static void MatchFinderMt_GetNextBlock_Hash(CMatchFinderMt *p)
{
  MtSync_GetNextBlock(&p->hashSync);
  p->hashBufPosLimit = p->hashBufPos = ((p->hashSync.numProcessedBlocks - 1) & kMtHashNumBlocksMask) * kMtHashBlockSize;
  p->hashBufPosLimit += p->hashBuf[p->hashBufPos++];
  p->hashNumAvail = p->hashBuf[p->hashBufPos++];
}