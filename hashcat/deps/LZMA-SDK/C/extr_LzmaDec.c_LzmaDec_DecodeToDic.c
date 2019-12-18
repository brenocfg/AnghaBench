#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
struct TYPE_6__ {scalar_t__ remainLen; scalar_t__ tempBufSize; scalar_t__* tempBuf; int code; int range; int* probs; int* reps; scalar_t__ dicPos; scalar_t__ const* buf; scalar_t__ state; int /*<<< orphan*/  prop; } ;
typedef  scalar_t__ SizeT ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ELzmaStatus ;
typedef  scalar_t__ ELzmaFinishMode ;
typedef  int CLzmaProb ;
typedef  TYPE_1__ CLzmaDec ;
typedef  scalar_t__ Byte ;

/* Variables and functions */
 int DUMMY_ERROR ; 
 int DUMMY_MATCH ; 
 scalar_t__ LZMA_FINISH_ANY ; 
 scalar_t__ LZMA_REQUIRED_INPUT_MAX ; 
 int /*<<< orphan*/  LZMA_STATUS_FINISHED_WITH_MARK ; 
 int /*<<< orphan*/  LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK ; 
 int /*<<< orphan*/  LZMA_STATUS_NEEDS_MORE_INPUT ; 
 int /*<<< orphan*/  LZMA_STATUS_NOT_FINISHED ; 
 int /*<<< orphan*/  LZMA_STATUS_NOT_SPECIFIED ; 
 scalar_t__ LzmaDec_DecodeReal2 (TYPE_1__*,scalar_t__,scalar_t__ const*) ; 
 int LzmaDec_TryDummy (TYPE_1__*,scalar_t__ const*,scalar_t__) ; 
 int /*<<< orphan*/  LzmaDec_WriteRem (TYPE_1__*,scalar_t__) ; 
 scalar_t__ LzmaProps_GetNumProbs (int /*<<< orphan*/ *) ; 
 scalar_t__ RC_INIT_SIZE ; 
 int /*<<< orphan*/  SZ_ERROR_DATA ; 
 int /*<<< orphan*/  SZ_ERROR_FAIL ; 
 int /*<<< orphan*/  SZ_OK ; 
 int kBitModelTotal ; 
 scalar_t__ kMatchSpecLenStart ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,scalar_t__) ; 

SRes LzmaDec_DecodeToDic(CLzmaDec *p, SizeT dicLimit, const Byte *src, SizeT *srcLen,
    ELzmaFinishMode finishMode, ELzmaStatus *status)
{
  SizeT inSize = *srcLen;
  (*srcLen) = 0;
  
  *status = LZMA_STATUS_NOT_SPECIFIED;

  if (p->remainLen > kMatchSpecLenStart)
  {
    for (; inSize > 0 && p->tempBufSize < RC_INIT_SIZE; (*srcLen)++, inSize--)
      p->tempBuf[p->tempBufSize++] = *src++;
    if (p->tempBufSize != 0 && p->tempBuf[0] != 0)
      return SZ_ERROR_DATA;
    if (p->tempBufSize < RC_INIT_SIZE)
    {
      *status = LZMA_STATUS_NEEDS_MORE_INPUT;
      return SZ_OK;
    }
    p->code =
        ((UInt32)p->tempBuf[1] << 24)
      | ((UInt32)p->tempBuf[2] << 16)
      | ((UInt32)p->tempBuf[3] << 8)
      | ((UInt32)p->tempBuf[4]);
    p->range = 0xFFFFFFFF;
    p->tempBufSize = 0;

    if (p->remainLen > kMatchSpecLenStart + 1)
    {
      SizeT numProbs = LzmaProps_GetNumProbs(&p->prop);
      SizeT i;
      CLzmaProb *probs = p->probs;
      for (i = 0; i < numProbs; i++)
        probs[i] = kBitModelTotal >> 1;
      p->reps[0] = p->reps[1] = p->reps[2] = p->reps[3] = 1;
      p->state = 0;
    }

    p->remainLen = 0;
  }

  LzmaDec_WriteRem(p, dicLimit);

  while (p->remainLen != kMatchSpecLenStart)
  {
      int checkEndMarkNow = 0;

      if (p->dicPos >= dicLimit)
      {
        if (p->remainLen == 0 && p->code == 0)
        {
          *status = LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK;
          return SZ_OK;
        }
        if (finishMode == LZMA_FINISH_ANY)
        {
          *status = LZMA_STATUS_NOT_FINISHED;
          return SZ_OK;
        }
        if (p->remainLen != 0)
        {
          *status = LZMA_STATUS_NOT_FINISHED;
          return SZ_ERROR_DATA;
        }
        checkEndMarkNow = 1;
      }

      if (p->tempBufSize == 0)
      {
        SizeT processed;
        const Byte *bufLimit;
        if (inSize < LZMA_REQUIRED_INPUT_MAX || checkEndMarkNow)
        {
          int dummyRes = LzmaDec_TryDummy(p, src, inSize);
          if (dummyRes == DUMMY_ERROR)
          {
            memcpy(p->tempBuf, src, inSize);
            p->tempBufSize = (unsigned)inSize;
            (*srcLen) += inSize;
            *status = LZMA_STATUS_NEEDS_MORE_INPUT;
            return SZ_OK;
          }
          if (checkEndMarkNow && dummyRes != DUMMY_MATCH)
          {
            *status = LZMA_STATUS_NOT_FINISHED;
            return SZ_ERROR_DATA;
          }
          bufLimit = src;
        }
        else
          bufLimit = src + inSize - LZMA_REQUIRED_INPUT_MAX;
        p->buf = src;
        if (LzmaDec_DecodeReal2(p, dicLimit, bufLimit) != 0)
          return SZ_ERROR_DATA;
        processed = (SizeT)(p->buf - src);
        (*srcLen) += processed;
        src += processed;
        inSize -= processed;
      }
      else
      {
        unsigned rem = p->tempBufSize, lookAhead = 0;
        while (rem < LZMA_REQUIRED_INPUT_MAX && lookAhead < inSize)
          p->tempBuf[rem++] = src[lookAhead++];
        p->tempBufSize = rem;
        if (rem < LZMA_REQUIRED_INPUT_MAX || checkEndMarkNow)
        {
          int dummyRes = LzmaDec_TryDummy(p, p->tempBuf, (SizeT)rem);
          if (dummyRes == DUMMY_ERROR)
          {
            (*srcLen) += (SizeT)lookAhead;
            *status = LZMA_STATUS_NEEDS_MORE_INPUT;
            return SZ_OK;
          }
          if (checkEndMarkNow && dummyRes != DUMMY_MATCH)
          {
            *status = LZMA_STATUS_NOT_FINISHED;
            return SZ_ERROR_DATA;
          }
        }
        p->buf = p->tempBuf;
        if (LzmaDec_DecodeReal2(p, dicLimit, p->buf) != 0)
          return SZ_ERROR_DATA;
        
        {
          unsigned kkk = (unsigned)(p->buf - p->tempBuf);
          if (rem < kkk)
            return SZ_ERROR_FAIL; /* some internal error */
          rem -= kkk;
          if (lookAhead < rem)
            return SZ_ERROR_FAIL; /* some internal error */
          lookAhead -= rem;
        }
        (*srcLen) += (SizeT)lookAhead;
        src += lookAhead;
        inSize -= (SizeT)lookAhead;
        p->tempBufSize = 0;
      }
  }
  
  if (p->code != 0)
    return SZ_ERROR_DATA;
  *status = LZMA_STATUS_FINISHED_WITH_MARK;
  return SZ_OK;
}