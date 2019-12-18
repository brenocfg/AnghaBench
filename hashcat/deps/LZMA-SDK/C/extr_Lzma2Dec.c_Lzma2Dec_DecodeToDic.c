#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt32 ;
struct TYPE_9__ {scalar_t__ dicPos; } ;
struct TYPE_8__ {scalar_t__ state; scalar_t__ unpackSize; int control; scalar_t__ packSize; TYPE_2__ decoder; } ;
typedef  scalar_t__ SizeT ;
typedef  scalar_t__ SRes ;
typedef  scalar_t__ ELzmaStatus ;
typedef  scalar_t__ ELzmaFinishMode ;
typedef  TYPE_1__ CLzma2Dec ;
typedef  int /*<<< orphan*/  Byte ;
typedef  int BoolInt ;

/* Variables and functions */
 int False ; 
 int LZMA2_CONTROL_COPY_RESET_DIC ; 
 scalar_t__ LZMA2_IS_UNCOMPRESSED_STATE (TYPE_1__*) ; 
 scalar_t__ LZMA2_STATE_CONTROL ; 
 scalar_t__ LZMA2_STATE_DATA ; 
 scalar_t__ LZMA2_STATE_DATA_CONT ; 
 scalar_t__ LZMA2_STATE_ERROR ; 
 scalar_t__ LZMA2_STATE_FINISHED ; 
 scalar_t__ LZMA_FINISH_ANY ; 
 scalar_t__ LZMA_FINISH_END ; 
 scalar_t__ LZMA_STATUS_FINISHED_WITH_MARK ; 
 scalar_t__ LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK ; 
 scalar_t__ LZMA_STATUS_NEEDS_MORE_INPUT ; 
 scalar_t__ LZMA_STATUS_NOT_FINISHED ; 
 scalar_t__ LZMA_STATUS_NOT_SPECIFIED ; 
 scalar_t__ Lzma2Dec_UpdateState (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ LzmaDec_DecodeToDic (TYPE_2__*,scalar_t__,int /*<<< orphan*/  const*,scalar_t__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  LzmaDec_InitDicAndState (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  LzmaDec_UpdateWithUncompressed (TYPE_2__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ SZ_ERROR_DATA ; 
 scalar_t__ SZ_OK ; 

SRes Lzma2Dec_DecodeToDic(CLzma2Dec *p, SizeT dicLimit,
    const Byte *src, SizeT *srcLen, ELzmaFinishMode finishMode, ELzmaStatus *status)
{
  SizeT inSize = *srcLen;
  *srcLen = 0;
  *status = LZMA_STATUS_NOT_SPECIFIED;

  while (p->state != LZMA2_STATE_ERROR)
  {
    SizeT dicPos;

    if (p->state == LZMA2_STATE_FINISHED)
    {
      *status = LZMA_STATUS_FINISHED_WITH_MARK;
      return SZ_OK;
    }
    
    dicPos = p->decoder.dicPos;
    
    if (dicPos == dicLimit && finishMode == LZMA_FINISH_ANY)
    {
      *status = LZMA_STATUS_NOT_FINISHED;
      return SZ_OK;
    }

    if (p->state != LZMA2_STATE_DATA && p->state != LZMA2_STATE_DATA_CONT)
    {
      if (*srcLen == inSize)
      {
        *status = LZMA_STATUS_NEEDS_MORE_INPUT;
        return SZ_OK;
      }
      (*srcLen)++;
      p->state = Lzma2Dec_UpdateState(p, *src++);
      if (dicPos == dicLimit && p->state != LZMA2_STATE_FINISHED)
        break;
      continue;
    }
    
    {
      SizeT inCur = inSize - *srcLen;
      SizeT outCur = dicLimit - dicPos;
      ELzmaFinishMode curFinishMode = LZMA_FINISH_ANY;
      
      if (outCur >= p->unpackSize)
      {
        outCur = (SizeT)p->unpackSize;
        curFinishMode = LZMA_FINISH_END;
      }

      if (LZMA2_IS_UNCOMPRESSED_STATE(p))
      {
        if (inCur == 0)
        {
          *status = LZMA_STATUS_NEEDS_MORE_INPUT;
          return SZ_OK;
        }

        if (p->state == LZMA2_STATE_DATA)
        {
          BoolInt initDic = (p->control == LZMA2_CONTROL_COPY_RESET_DIC);
          LzmaDec_InitDicAndState(&p->decoder, initDic, False);
        }

        if (inCur > outCur)
          inCur = outCur;
        if (inCur == 0)
          break;

        LzmaDec_UpdateWithUncompressed(&p->decoder, src, inCur);

        src += inCur;
        *srcLen += inCur;
        p->unpackSize -= (UInt32)inCur;
        p->state = (p->unpackSize == 0) ? LZMA2_STATE_CONTROL : LZMA2_STATE_DATA_CONT;
      }
      else
      {
        SRes res;

        if (p->state == LZMA2_STATE_DATA)
        {
          BoolInt initDic = (p->control >= 0xE0);
          BoolInt initState = (p->control >= 0xA0);
          LzmaDec_InitDicAndState(&p->decoder, initDic, initState);
          p->state = LZMA2_STATE_DATA_CONT;
        }
  
        if (inCur > p->packSize)
          inCur = (SizeT)p->packSize;
        
        res = LzmaDec_DecodeToDic(&p->decoder, dicPos + outCur, src, &inCur, curFinishMode, status);

        src += inCur;
        *srcLen += inCur;
        p->packSize -= (UInt32)inCur;
        outCur = p->decoder.dicPos - dicPos;
        p->unpackSize -= (UInt32)outCur;

        if (res != 0)
          break;
        
        if (*status == LZMA_STATUS_NEEDS_MORE_INPUT)
        {
          if (p->packSize == 0)
            break;
          return SZ_OK;
        }

        if (inCur == 0 && outCur == 0)
        {
          if (*status != LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK
              || p->unpackSize != 0
              || p->packSize != 0)
            break;
          p->state = LZMA2_STATE_CONTROL;
        }
        
        *status = LZMA_STATUS_NOT_SPECIFIED;
      }
    }
  }
  
  *status = LZMA_STATUS_NOT_SPECIFIED;
  p->state = LZMA2_STATE_ERROR;
  return SZ_ERROR_DATA;
}