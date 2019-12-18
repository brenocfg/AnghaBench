#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt64 ;
struct TYPE_10__ {scalar_t__ dicPos; scalar_t__ dicBufSize; scalar_t__ dic; } ;
struct TYPE_12__ {TYPE_2__ decoder; } ;
struct TYPE_9__ {scalar_t__ outStep_ST; } ;
struct TYPE_11__ {scalar_t__ inProcessed; scalar_t__ outProcessed; size_t inBufSize; scalar_t__ readRes; scalar_t__ outSize; scalar_t__ progress; scalar_t__ finishMode; scalar_t__ outSize_Defined; int /*<<< orphan*/  outStream; TYPE_1__ props; scalar_t__ readWasFinished; int /*<<< orphan*/  inStream; int /*<<< orphan*/ * inBuf; int /*<<< orphan*/  mtc; TYPE_4__ dec; } ;
typedef  scalar_t__ SizeT ;
typedef  scalar_t__ SRes ;
typedef  scalar_t__ ELzmaStatus ;
typedef  int /*<<< orphan*/  ELzmaFinishMode ;
typedef  TYPE_3__ CLzma2DecMt ;
typedef  TYPE_4__ CLzma2Dec ;
typedef  int /*<<< orphan*/  Byte ;
typedef  int BoolInt ;

/* Variables and functions */
 int False ; 
 scalar_t__ ICompressProgress_Progress (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ ISeqInStream_Read (int /*<<< orphan*/ ,void*,size_t*) ; 
 size_t ISeqOutStream_Write (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  LZMA_FINISH_ANY ; 
 int /*<<< orphan*/  LZMA_FINISH_END ; 
 scalar_t__ LZMA_STATUS_FINISHED_WITH_MARK ; 
 scalar_t__ LZMA_STATUS_NEEDS_MORE_INPUT ; 
 int /*<<< orphan*/  Lzma2DecMt_FreeOutBufs (TYPE_3__*) ; 
 scalar_t__ Lzma2Dec_DecodeToDic (TYPE_4__*,scalar_t__,int /*<<< orphan*/  const*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ Lzma2Dec_Prepare_ST (TYPE_3__*) ; 
 int MtDec_PrepareRead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MtDec_Read (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  RINOK (scalar_t__) ; 
 scalar_t__ SZ_ERROR_DATA ; 
 scalar_t__ SZ_ERROR_INPUT_EOF ; 
 scalar_t__ SZ_ERROR_WRITE ; 
 scalar_t__ SZ_OK ; 
 scalar_t__ True ; 

__attribute__((used)) static SRes Lzma2Dec_Decode_ST(CLzma2DecMt *p
    #ifndef _7ZIP_ST
    , BoolInt tMode
    #endif
    )
{
  SizeT wrPos;
  size_t inPos, inLim;
  const Byte *inData;
  UInt64 inPrev, outPrev;

  CLzma2Dec *dec;

  #ifndef _7ZIP_ST
  if (tMode)
  {
    Lzma2DecMt_FreeOutBufs(p);
    tMode = MtDec_PrepareRead(&p->mtc);
  }
  #endif

  RINOK(Lzma2Dec_Prepare_ST(p));

  dec = &p->dec;

  inPrev = p->inProcessed;
  outPrev = p->outProcessed;

  inPos = 0;
  inLim = 0;
  inData = NULL;
  wrPos = dec->decoder.dicPos;

  for (;;)
  {
    SizeT dicPos;
    SizeT size;
    ELzmaFinishMode finishMode;
    SizeT inProcessed;
    ELzmaStatus status;
    SRes res;

    SizeT outProcessed;
    BoolInt outFinished;
    BoolInt needStop;

    if (inPos == inLim)
    {
      #ifndef _7ZIP_ST
      if (tMode)
      {
        inData = MtDec_Read(&p->mtc, &inLim);
        inPos = 0;
        if (inData)
          continue;
        tMode = False;
        inLim = 0;
      }
      #endif
      
      if (!p->readWasFinished)
      {
        inPos = 0;
        inLim = p->inBufSize;
        inData = p->inBuf;
        p->readRes = ISeqInStream_Read(p->inStream, (void *)inData, &inLim);
        // p->readProcessed += inLim;
        // inLim -= 5; p->readWasFinished = True; // for test
        if (inLim == 0 || p->readRes != SZ_OK)
          p->readWasFinished = True;
      }
    }

    dicPos = dec->decoder.dicPos;
    {
      SizeT next = dec->decoder.dicBufSize;
      if (next - wrPos > p->props.outStep_ST)
        next = wrPos + p->props.outStep_ST;
      size = next - dicPos;
    }

    finishMode = LZMA_FINISH_ANY;
    if (p->outSize_Defined)
    {
      const UInt64 rem = p->outSize - p->outProcessed;
      if (size >= rem)
      {
        size = (SizeT)rem;
        if (p->finishMode)
          finishMode = LZMA_FINISH_END;
      }
    }

    inProcessed = inLim - inPos;
    
    res = Lzma2Dec_DecodeToDic(dec, dicPos + size, inData + inPos, &inProcessed, finishMode, &status);

    inPos += inProcessed;
    p->inProcessed += inProcessed;
    outProcessed = dec->decoder.dicPos - dicPos;
    p->outProcessed += outProcessed;

    outFinished = (p->outSize_Defined && p->outSize <= p->outProcessed);

    needStop = (res != SZ_OK
        || (inProcessed == 0 && outProcessed == 0)
        || status == LZMA_STATUS_FINISHED_WITH_MARK
        || (!p->finishMode && outFinished));

    if (needStop || outProcessed >= size)
    {
      SRes res2;
      {
        size_t writeSize = dec->decoder.dicPos - wrPos;
        size_t written = ISeqOutStream_Write(p->outStream, dec->decoder.dic + wrPos, writeSize);
        res2 = (written == writeSize) ? SZ_OK : SZ_ERROR_WRITE;
      }

      if (dec->decoder.dicPos == dec->decoder.dicBufSize)
        dec->decoder.dicPos = 0;
      wrPos = dec->decoder.dicPos;

      RINOK(res2);

      if (needStop)
      {
        if (res != SZ_OK)
          return res;

        if (status == LZMA_STATUS_FINISHED_WITH_MARK)
        {
          if (p->finishMode)
          {
            if (p->outSize_Defined && p->outSize != p->outProcessed)
              return SZ_ERROR_DATA;
          }
          return SZ_OK;
        }

        if (!p->finishMode && outFinished)
          return SZ_OK;

        if (status == LZMA_STATUS_NEEDS_MORE_INPUT)
          return SZ_ERROR_INPUT_EOF;
        
        return SZ_ERROR_DATA;
      }
    }
    
    if (p->progress)
    {
      UInt64 inDelta = p->inProcessed - inPrev;
      UInt64 outDelta = p->outProcessed - outPrev;
      if (inDelta >= (1 << 22) || outDelta >= (1 << 22))
      {
        RINOK(ICompressProgress_Progress(p->progress, p->inProcessed, p->outProcessed));
        inPrev = p->inProcessed;
        outPrev = p->outProcessed;
      }
    }
  }
}