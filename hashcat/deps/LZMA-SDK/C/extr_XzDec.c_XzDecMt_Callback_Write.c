#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  size_t UInt64 ;
struct TYPE_18__ {size_t totalInSize; } ;
struct TYPE_12__ {scalar_t__ inProcessed; int readWasFinished; size_t crossStart; size_t crossEnd; size_t inBufSize; scalar_t__ readRes; size_t readProcessed; TYPE_9__ mtProgress; scalar_t__ progress; } ;
struct TYPE_15__ {scalar_t__ state; void* decodeToStreamSignature; int /*<<< orphan*/  numTotalBlocks; int /*<<< orphan*/  streamFlags; int /*<<< orphan*/  numStartedStreams; void* decodeOnlyOneBlock; } ;
struct TYPE_13__ {scalar_t__ ignoreErrors; } ;
struct TYPE_17__ {scalar_t__ finishedDecoderIndex; scalar_t__ mainErrorCode; scalar_t__ writeRes; size_t outSize; size_t outProcessed; TYPE_11__ mtc; void* isBlockHeaderState_Write; void* isBlockHeaderState_Parse; scalar_t__ status; scalar_t__ codeRes; int /*<<< orphan*/  inStream; void* parsing_Truncated; void* mainDecoderWasCalled; TYPE_3__ dec; TYPE_1__ props; int /*<<< orphan*/  outStream; scalar_t__ outSize_Defined; TYPE_4__* coders; } ;
struct TYPE_14__ {int /*<<< orphan*/  numTotalBlocks; int /*<<< orphan*/  numStartedStreams; int /*<<< orphan*/  headerParsedOk; } ;
struct TYPE_16__ {scalar_t__ inCodeSize; size_t outCodeSize; size_t outPreSize; scalar_t__ codeRes; scalar_t__ inPreSize; scalar_t__ blockPackTotal; scalar_t__ parseState; scalar_t__ parsing_Truncated; scalar_t__ status; int /*<<< orphan*/  blockPackSize_for_Index; TYPE_2__ dec; int /*<<< orphan*/  streamFlags; int /*<<< orphan*/ * outBuf; } ;
typedef  size_t SizeT ;
typedef  scalar_t__ SRes ;
typedef  scalar_t__ ECoderStatus ;
typedef  TYPE_3__ CXzUnpacker ;
typedef  TYPE_4__ CXzDecMtThread ;
typedef  TYPE_5__ CXzDecMt ;
typedef  int /*<<< orphan*/  Byte ;
typedef  void* BoolInt ;

/* Variables and functions */
 int /*<<< orphan*/  CODER_FINISH_END ; 
 scalar_t__ CODER_STATUS_NEEDS_MORE_INPUT ; 
 scalar_t__ E_FAIL ; 
 void* False ; 
 scalar_t__ ISeqInStream_Read (int /*<<< orphan*/ ,void*,size_t*) ; 
 size_t ISeqOutStream_Write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int LZMA_STATUS_NEEDS_MORE_INPUT ; 
 scalar_t__ MTDEC_PARSE_END ; 
 int /*<<< orphan*/ * MtDec_GetCrossBuff (TYPE_11__*) ; 
 scalar_t__ MtProgress_ProgressAdd (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MtProgress_Progress_ST (TYPE_9__*) ; 
 int /*<<< orphan*/  PRF_STR_INT (char*,size_t) ; 
 int /*<<< orphan*/  RINOK (scalar_t__) ; 
 scalar_t__ SZ_ERROR_DATA ; 
 scalar_t__ SZ_ERROR_INPUT_EOF ; 
 scalar_t__ SZ_ERROR_MEM ; 
 scalar_t__ SZ_ERROR_WRITE ; 
 scalar_t__ SZ_OK ; 
 scalar_t__ S_OK ; 
 void* True ; 
 size_t XZDECMT_STREAM_WRITE_STEP ; 
 scalar_t__ XZ_STATE_STREAM_HEADER ; 
 scalar_t__ XzUnpacker_Code (TYPE_3__*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/  const*,size_t*,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  XzUnpacker_PrepareToRandomBlockDecoding (TYPE_3__*) ; 
 int /*<<< orphan*/  XzUnpacker_UpdateIndex (TYPE_3__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static SRes XzDecMt_Callback_Write(void *pp, unsigned coderIndex,
    BoolInt needWriteToStream,
    const Byte *src, size_t srcSize,
    // int srcFinished,
    BoolInt *needContinue,
    BoolInt *canRecode)
{
  CXzDecMt *me = (CXzDecMt *)pp;
  const CXzDecMtThread *coder = &me->coders[coderIndex];

  // PRF(printf("\nWrite processed = %d srcSize = %d\n", (unsigned)me->mtc.inProcessed, (unsigned)srcSize));
  
  *needContinue = False;
  *canRecode = True;
  
  if (!needWriteToStream)
    return SZ_OK;

  if (!coder->dec.headerParsedOk || !coder->outBuf)
  {
    if (me->finishedDecoderIndex < 0)
      me->finishedDecoderIndex = coderIndex;
    return SZ_OK;
  }

  if (me->finishedDecoderIndex >= 0)
    return SZ_OK;

  me->mtc.inProcessed += coder->inCodeSize;

  *canRecode = False;

  {
    SRes res;
    size_t size = coder->outCodeSize;
    Byte *data = coder->outBuf;
    
    // we use in me->dec: sha, numBlocks, indexSize

    if (!me->isBlockHeaderState_Write)
    {
      XzUnpacker_PrepareToRandomBlockDecoding(&me->dec);
      me->dec.decodeOnlyOneBlock = False;
      me->dec.numStartedStreams = coder->dec.numStartedStreams;
      me->dec.streamFlags = coder->streamFlags;

      me->isBlockHeaderState_Write = True;
    }
    
    me->dec.numTotalBlocks = coder->dec.numTotalBlocks;
    XzUnpacker_UpdateIndex(&me->dec, coder->blockPackSize_for_Index, coder->outPreSize);
    
    if (coder->outPreSize != size)
    {
      if (me->props.ignoreErrors)
      {
        memset(data + size, 0, coder->outPreSize - size);
        size = coder->outPreSize;
      }
      // me->numBadBlocks++;
      if (me->mainErrorCode == SZ_OK)
      {
        if ((int)coder->status == LZMA_STATUS_NEEDS_MORE_INPUT)
          me->mainErrorCode = SZ_ERROR_INPUT_EOF;
        else
          me->mainErrorCode = SZ_ERROR_DATA;
      }
    }
    
    if (me->writeRes != SZ_OK)
      return me->writeRes;

    res = SZ_OK;
    {
      if (me->outSize_Defined)
      {
        const UInt64 rem = me->outSize - me->outProcessed;
        if (size > rem)
          size = (SizeT)rem;
      }

      for (;;)
      {
        size_t cur = size;
        size_t written;
        if (cur > XZDECMT_STREAM_WRITE_STEP)
          cur = XZDECMT_STREAM_WRITE_STEP;

        written = ISeqOutStream_Write(me->outStream, data, cur);

        // PRF(printf("\nWritten ask = %d written = %d\n", (unsigned)cur, (unsigned)written));
        
        me->outProcessed += written;
        if (written != cur)
        {
          me->writeRes = SZ_ERROR_WRITE;
          res = me->writeRes;
          break;
        }
        data += cur;
        size -= cur;
        // PRF_STR_INT("Written size =", size);
        if (size == 0)
          break;
        res = MtProgress_ProgressAdd(&me->mtc.mtProgress, 0, 0);
        if (res != SZ_OK)
          break;
      }
    }

    if (coder->codeRes != SZ_OK)
      if (!me->props.ignoreErrors)
      {
        me->finishedDecoderIndex = coderIndex;
        return res;
      }

    RINOK(res);

    if (coder->inPreSize != coder->inCodeSize
        || coder->blockPackTotal != coder->inCodeSize)
    {
      me->finishedDecoderIndex = coderIndex;
      return SZ_OK;
    }

    if (coder->parseState != MTDEC_PARSE_END)
    {
      *needContinue = True;
      return SZ_OK;
    }
  }

  // (coder->state == MTDEC_PARSE_END) means that there are no other working threads
  // so we can use mtc variables without lock

  PRF_STR_INT("Write MTDEC_PARSE_END", me->mtc.inProcessed);

  me->mtc.mtProgress.totalInSize = me->mtc.inProcessed;
  {
    CXzUnpacker *dec = &me->dec;
    
    PRF_STR_INT("PostSingle", srcSize);
    
    {
      size_t srcProcessed = srcSize;
      ECoderStatus status;
      size_t outSizeCur = 0;
      SRes res;
      
      // dec->decodeOnlyOneBlock = False;
      dec->decodeToStreamSignature = True;

      me->mainDecoderWasCalled = True;

      if (coder->parsing_Truncated)
      {
        me->parsing_Truncated = True;
        return SZ_OK;
      }
      
      res = XzUnpacker_Code(dec,
          NULL, &outSizeCur,
          src, &srcProcessed,
          me->mtc.readWasFinished, // srcFinished
          CODER_FINISH_END, // CODER_FINISH_ANY,
          &status);
      
      me->status = status;
      me->codeRes = res;

      me->mtc.inProcessed += srcProcessed;
      me->mtc.mtProgress.totalInSize = me->mtc.inProcessed;

      if (res != SZ_OK)
      {
        return S_OK;
        // return res;
      }
      
      if (dec->state == XZ_STATE_STREAM_HEADER)
      {
        *needContinue = True;
        me->isBlockHeaderState_Parse = False;
        me->isBlockHeaderState_Write = False;
        {
          Byte *crossBuf = MtDec_GetCrossBuff(&me->mtc);
          if (!crossBuf)
            return SZ_ERROR_MEM;
          memcpy(crossBuf, src + srcProcessed, srcSize - srcProcessed);
        }
        me->mtc.crossStart = 0;
        me->mtc.crossEnd = srcSize - srcProcessed;
        return SZ_OK;
      }
      
      if (status != CODER_STATUS_NEEDS_MORE_INPUT)
      {
        return E_FAIL;
      }
      
      if (me->mtc.readWasFinished)
      {
        return SZ_OK;
      }
    }
    
    {
      size_t inPos;
      size_t inLim;
      const Byte *inData;
      UInt64 inProgressPrev = me->mtc.inProcessed;
      
      // XzDecMt_Prepare_InBuf_ST(p);
      Byte *crossBuf = MtDec_GetCrossBuff(&me->mtc);
      if (!crossBuf)
        return SZ_ERROR_MEM;
      
      inPos = 0;
      inLim = 0;
      // outProcessed = 0;
      
      inData = crossBuf;
      
      for (;;)
      {
        SizeT inProcessed;
        SizeT outProcessed;
        ECoderStatus status;
        SRes res;
        
        if (inPos == inLim)
        {
          if (!me->mtc.readWasFinished)
          {
            inPos = 0;
            inLim = me->mtc.inBufSize;
            me->mtc.readRes = ISeqInStream_Read(me->inStream, (void *)inData, &inLim);
            me->mtc.readProcessed += inLim;
            if (inLim == 0 || me->mtc.readRes != SZ_OK)
              me->mtc.readWasFinished = True;
          }
        }
        
        inProcessed = inLim - inPos;
        outProcessed = 0;

        res = XzUnpacker_Code(dec,
            NULL, &outProcessed,
            inData + inPos, &inProcessed,
            (inProcessed == 0), // srcFinished
            CODER_FINISH_END, &status);
        
        me->codeRes = res;
        me->status = status;
        inPos += inProcessed;
        me->mtc.inProcessed += inProcessed;
        me->mtc.mtProgress.totalInSize = me->mtc.inProcessed;

        if (res != SZ_OK)
        {
          return S_OK;
          // return res;
        }

        if (dec->state == XZ_STATE_STREAM_HEADER)
        {
          *needContinue = True;
          me->mtc.crossStart = inPos;
          me->mtc.crossEnd = inLim;
          me->isBlockHeaderState_Parse = False;
          me->isBlockHeaderState_Write = False;
          return SZ_OK;
        }
        
        if (status != CODER_STATUS_NEEDS_MORE_INPUT)
          return E_FAIL;
        
        if (me->mtc.progress)
        {
          UInt64 inDelta = me->mtc.inProcessed - inProgressPrev;
          if (inDelta >= (1 << 22))
          {
            RINOK(MtProgress_Progress_ST(&me->mtc.mtProgress));
            inProgressPrev = me->mtc.inProcessed;
          }
        }
        if (me->mtc.readWasFinished)
          return SZ_OK;
      }
    }
  }
}