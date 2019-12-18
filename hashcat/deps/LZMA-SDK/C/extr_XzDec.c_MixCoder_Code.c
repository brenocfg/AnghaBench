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
struct TYPE_5__ {scalar_t__ res; scalar_t__ status; scalar_t__ outWritten; int numCoders; int* pos; scalar_t__* size; int* finished; scalar_t__* results; int /*<<< orphan*/ * buf; TYPE_1__* coders; int /*<<< orphan*/  alloc; scalar_t__ outBuf; void* wasFinished; } ;
struct TYPE_4__ {scalar_t__ (* Code2 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/  const*,scalar_t__*,int,int /*<<< orphan*/ ,scalar_t__*) ;size_t (* Filter ) (int /*<<< orphan*/ ,scalar_t__,size_t) ;int /*<<< orphan*/  p; } ;
typedef  scalar_t__ SizeT ;
typedef  scalar_t__ SRes ;
typedef  TYPE_1__ IStateCoder ;
typedef  scalar_t__ ECoderStatus ;
typedef  int /*<<< orphan*/  ECoderFinishMode ;
typedef  TYPE_2__ CMixCoder ;
typedef  int /*<<< orphan*/  Byte ;
typedef  void* BoolInt ;

/* Variables and functions */
 int CODER_BUF_SIZE ; 
 int /*<<< orphan*/  CODER_FINISH_ANY ; 
 scalar_t__ CODER_STATUS_FINISHED_WITH_MARK ; 
 void* CODER_STATUS_NOT_FINISHED ; 
 void* False ; 
 scalar_t__ ISzAlloc_Alloc (int /*<<< orphan*/ ,int) ; 
 int MIXCODER_NUM_FILTERS_MAX ; 
 int /*<<< orphan*/  PRF_STR (char*) ; 
 int /*<<< orphan*/  PRF_STR_INT (char*,unsigned int) ; 
 scalar_t__ SZ_ERROR_MEM ; 
 scalar_t__ SZ_OK ; 
 void* True ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/  const*,scalar_t__*,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 size_t stub2 (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/  const*,scalar_t__*,int,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static SRes MixCoder_Code(CMixCoder *p,
    Byte *dest, SizeT *destLen, int destFinish,
    const Byte *src, SizeT *srcLen, int srcWasFinished,
    ECoderFinishMode finishMode)
{
  SizeT destLenOrig = *destLen;
  SizeT srcLenOrig = *srcLen;

  *destLen = 0;
  *srcLen = 0;

  if (p->wasFinished)
    return p->res;
  
  p->status = CODER_STATUS_NOT_FINISHED;

  // if (p->SingleBufMode)
  if (p->outBuf)
  {
    SRes res;
    SizeT destLen2, srcLen2;
    int wasFinished;
    
    PRF_STR("------- MixCoder Single ----------");
      
    srcLen2 = srcLenOrig;
    destLen2 = destLenOrig;
    
    {
      IStateCoder *coder = &p->coders[0];
      res = coder->Code2(coder->p, NULL, &destLen2, src, &srcLen2, srcWasFinished, finishMode,
          // &wasFinished,
          &p->status);
      wasFinished = (p->status == CODER_STATUS_FINISHED_WITH_MARK);
    }
    
    p->res = res;
    
    /*
    if (wasFinished)
      p->status = CODER_STATUS_FINISHED_WITH_MARK;
    else
    {
      if (res == SZ_OK)
        if (destLen2 != destLenOrig)
          p->status = CODER_STATUS_NEEDS_MORE_INPUT;
    }
    */

    
    *srcLen = srcLen2;
    src += srcLen2;
    p->outWritten += destLen2;
    
    if (res != SZ_OK || srcWasFinished || wasFinished)
      p->wasFinished = True;
    
    if (p->numCoders == 1)
      *destLen = destLen2;
    else if (p->wasFinished)
    {
      unsigned i;
      size_t processed = p->outWritten;
      
      for (i = 1; i < p->numCoders; i++)
      {
        IStateCoder *coder = &p->coders[i];
        processed = coder->Filter(coder->p, p->outBuf, processed);
        if (wasFinished || (destFinish && p->outWritten == destLenOrig))
          processed = p->outWritten;
        PRF_STR_INT("filter", i);
      }
      *destLen = processed;
    }
    return res;
  }

  PRF_STR("standard mix");

  if (p->numCoders != 1)
  {
    if (!p->buf)
    {
      p->buf = (Byte *)ISzAlloc_Alloc(p->alloc, CODER_BUF_SIZE * (MIXCODER_NUM_FILTERS_MAX - 1));
      if (!p->buf)
        return SZ_ERROR_MEM;
    }
    
    finishMode = CODER_FINISH_ANY;
  }

  for (;;)
  {
    BoolInt processed = False;
    BoolInt allFinished = True;
    SRes resMain = SZ_OK;
    unsigned i;

    p->status = CODER_STATUS_NOT_FINISHED;
    /*
    if (p->numCoders == 1 && *destLen == destLenOrig && finishMode == LZMA_FINISH_ANY)
      break;
    */

    for (i = 0; i < p->numCoders; i++)
    {
      SRes res;
      IStateCoder *coder = &p->coders[i];
      Byte *dest2;
      SizeT destLen2, srcLen2; // destLen2_Orig;
      const Byte *src2;
      int srcFinished2;
      int encodingWasFinished;
      ECoderStatus status2;
      
      if (i == 0)
      {
        src2 = src;
        srcLen2 = srcLenOrig - *srcLen;
        srcFinished2 = srcWasFinished;
      }
      else
      {
        size_t k = i - 1;
        src2 = p->buf + (CODER_BUF_SIZE * k) + p->pos[k];
        srcLen2 = p->size[k] - p->pos[k];
        srcFinished2 = p->finished[k];
      }
      
      if (i == p->numCoders - 1)
      {
        dest2 = dest;
        destLen2 = destLenOrig - *destLen;
      }
      else
      {
        if (p->pos[i] != p->size[i])
          continue;
        dest2 = p->buf + (CODER_BUF_SIZE * i);
        destLen2 = CODER_BUF_SIZE;
      }
      
      // destLen2_Orig = destLen2;
      
      if (p->results[i] != SZ_OK)
      {
        if (resMain == SZ_OK)
          resMain = p->results[i];
        continue;
      }

      res = coder->Code2(coder->p,
          dest2, &destLen2,
          src2, &srcLen2, srcFinished2,
          finishMode,
          // &encodingWasFinished,
          &status2);

      if (res != SZ_OK)
      {
        p->results[i] = res;
        if (resMain == SZ_OK)
          resMain = res;
      }

      encodingWasFinished = (status2 == CODER_STATUS_FINISHED_WITH_MARK);
      
      if (!encodingWasFinished)
      {
        allFinished = False;
        if (p->numCoders == 1 && res == SZ_OK)
          p->status = status2;
      }

      if (i == 0)
      {
        *srcLen += srcLen2;
        src += srcLen2;
      }
      else
        p->pos[(size_t)i - 1] += srcLen2;

      if (i == p->numCoders - 1)
      {
        *destLen += destLen2;
        dest += destLen2;
      }
      else
      {
        p->size[i] = destLen2;
        p->pos[i] = 0;
        p->finished[i] = encodingWasFinished;
      }
      
      if (destLen2 != 0 || srcLen2 != 0)
        processed = True;
    }
    
    if (!processed)
    {
      if (allFinished)
        p->status = CODER_STATUS_FINISHED_WITH_MARK;
      return resMain;
    }
  }
}