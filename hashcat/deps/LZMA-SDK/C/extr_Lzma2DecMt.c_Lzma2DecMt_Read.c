#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UInt64 ;
struct TYPE_3__ {scalar_t__ inBufSize_ST; } ;
struct TYPE_4__ {size_t outSize; size_t outProcessed; scalar_t__ inPos; scalar_t__ inLim; size_t inBuf; int /*<<< orphan*/  inProcessed; int /*<<< orphan*/  dec; int /*<<< orphan*/  inStream; TYPE_1__ props; scalar_t__ finishMode; scalar_t__ outSize_Defined; } ;
typedef  size_t SizeT ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ELzmaStatus ;
typedef  int /*<<< orphan*/  ELzmaFinishMode ;
typedef  scalar_t__ CLzma2DecMtHandle ;
typedef  TYPE_2__ CLzma2DecMt ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ ISeqInStream_Read (int /*<<< orphan*/ ,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  LZMA_FINISH_ANY ; 
 int /*<<< orphan*/  LZMA_FINISH_END ; 
 scalar_t__ Lzma2Dec_DecodeToBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,size_t,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SZ_OK ; 

SRes Lzma2DecMt_Read(CLzma2DecMtHandle pp,
    Byte *data, size_t *outSize,
    UInt64 *inStreamProcessed)
{
  CLzma2DecMt *p = (CLzma2DecMt *)pp;
  ELzmaFinishMode finishMode;
  SRes readRes;
  size_t size = *outSize;

  *outSize = 0;
  *inStreamProcessed = 0;

  finishMode = LZMA_FINISH_ANY;
  if (p->outSize_Defined)
  {
    const UInt64 rem = p->outSize - p->outProcessed;
    if (size >= rem)
    {
      size = (size_t)rem;
      if (p->finishMode)
        finishMode = LZMA_FINISH_END;
    }
  }

  readRes = SZ_OK;

  for (;;)
  {
    SizeT inCur;
    SizeT outCur;
    ELzmaStatus status;
    SRes res;

    if (p->inPos == p->inLim && readRes == SZ_OK)
    {
      p->inPos = 0;
      p->inLim = p->props.inBufSize_ST;
      readRes = ISeqInStream_Read(p->inStream, p->inBuf, &p->inLim);
    }

    inCur = p->inLim - p->inPos;
    outCur = size;

    res = Lzma2Dec_DecodeToBuf(&p->dec, data, &outCur,
        p->inBuf + p->inPos, &inCur, finishMode, &status);
    
    p->inPos += inCur;
    p->inProcessed += inCur;
    *inStreamProcessed += inCur;
    p->outProcessed += outCur;
    *outSize += outCur;
    size -= outCur;
    data += outCur;
    
    if (res != 0)
      return res;
    
    /*
    if (status == LZMA_STATUS_FINISHED_WITH_MARK)
      return readRes;

    if (size == 0 && status != LZMA_STATUS_NEEDS_MORE_INPUT)
    {
      if (p->finishMode && p->outSize_Defined && p->outProcessed >= p->outSize)
        return SZ_ERROR_DATA;
      return readRes;
    }
    */

    if (inCur == 0 && outCur == 0)
      return readRes;
  }
}