#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt64 ;
struct TYPE_12__ {scalar_t__ res; } ;
struct TYPE_16__ {int numThreadsMax; scalar_t__ readRes; scalar_t__ inProcessed; void* readWasFinished; void* needContinue; TYPE_2__ mtProgress; int /*<<< orphan*/  inBufSize; TYPE_5__* mtCallbackObject; TYPE_3__* mtCallback; int /*<<< orphan*/ * alloc; int /*<<< orphan*/ * inStream; int /*<<< orphan*/ * progress; } ;
struct TYPE_14__ {int numThreads; int /*<<< orphan*/  inBufSize_MT; } ;
struct TYPE_11__ {int /*<<< orphan*/  vt; } ;
struct TYPE_15__ {int prop; int finishMode; scalar_t__ readRes; scalar_t__ inProcessed; TYPE_6__ mtc; void* readWasFinished; TYPE_4__ props; TYPE_1__ alignOffsetAlloc; void* mtc_WasConstructed; scalar_t__ outProcessed_Parse; scalar_t__ outProcessed; scalar_t__ outSize; void* outSize_Defined; int /*<<< orphan*/ * progress; int /*<<< orphan*/ * outStream; int /*<<< orphan*/ * inStream; } ;
struct TYPE_13__ {int /*<<< orphan*/  Write; int /*<<< orphan*/  Code; int /*<<< orphan*/  PreCode; int /*<<< orphan*/  Parse; } ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ISeqOutStream ;
typedef  int /*<<< orphan*/  ISeqInStream ;
typedef  TYPE_3__ IMtDecCallback ;
typedef  int /*<<< orphan*/  ICompressProgress ;
typedef  TYPE_4__ CLzma2DecMtProps ;
typedef  scalar_t__ CLzma2DecMtHandle ;
typedef  TYPE_5__ CLzma2DecMt ;
typedef  int Byte ;
typedef  void* BoolInt ;

/* Variables and functions */
 void* False ; 
 int /*<<< orphan*/  Lzma2DecMt_FreeSt (TYPE_5__*) ; 
 int /*<<< orphan*/  Lzma2DecMt_MtCallback_Code ; 
 int /*<<< orphan*/  Lzma2DecMt_MtCallback_Parse ; 
 int /*<<< orphan*/  Lzma2DecMt_MtCallback_PreCode ; 
 int /*<<< orphan*/  Lzma2DecMt_MtCallback_Write ; 
 scalar_t__ Lzma2Dec_Decode_ST (TYPE_5__*,void*) ; 
 scalar_t__ MtDec_Code (TYPE_6__*) ; 
 int /*<<< orphan*/  MtDec_Construct (TYPE_6__*) ; 
 int /*<<< orphan*/  PRF_STR (char*) ; 
 scalar_t__ SZ_ERROR_UNSUPPORTED ; 
 scalar_t__ SZ_OK ; 
 void* True ; 

SRes Lzma2DecMt_Decode(CLzma2DecMtHandle pp,
    Byte prop,
    const CLzma2DecMtProps *props,
    ISeqOutStream *outStream, const UInt64 *outDataSize, int finishMode,
    // Byte *outBuf, size_t *outBufSize,
    ISeqInStream *inStream,
    // const Byte *inData, size_t inDataSize,
    UInt64 *inProcessed,
    // UInt64 *outProcessed,
    int *isMT,
    ICompressProgress *progress)
{
  CLzma2DecMt *p = (CLzma2DecMt *)pp;
  #ifndef _7ZIP_ST
  BoolInt tMode;
  #endif

  *inProcessed = 0;

  if (prop > 40)
    return SZ_ERROR_UNSUPPORTED;

  p->prop = prop;
  p->props = *props;

  p->inStream = inStream;
  p->outStream = outStream;
  p->progress = progress;

  p->outSize = 0;
  p->outSize_Defined = False;
  if (outDataSize)
  {
    p->outSize_Defined = True;
    p->outSize = *outDataSize;
  }
  p->finishMode = finishMode;

  p->outProcessed = 0;
  p->inProcessed = 0;

  p->readWasFinished = False;

  *isMT = False;

  
  #ifndef _7ZIP_ST

  tMode = False;

  // p->mtc.parseRes = SZ_OK;

  // p->mtc.numFilledThreads = 0;
  // p->mtc.crossStart = 0;
  // p->mtc.crossEnd = 0;
  // p->mtc.allocError_for_Read_BlockIndex = 0;
  // p->mtc.isAllocError = False;

  if (p->props.numThreads > 1)
  {
    IMtDecCallback vt;

    Lzma2DecMt_FreeSt(p);

    p->outProcessed_Parse = 0;

    if (!p->mtc_WasConstructed)
    {
      p->mtc_WasConstructed = True;
      MtDec_Construct(&p->mtc);
    }
    
    p->mtc.progress = progress;
    p->mtc.inStream = inStream;

    // p->outBuf = NULL;
    // p->outBufSize = 0;
    /*
    if (!outStream)
    {
      // p->outBuf = outBuf;
      // p->outBufSize = *outBufSize;
      // *outBufSize = 0;
      return SZ_ERROR_PARAM;
    }
    */

    // p->mtc.inBlockMax = p->props.inBlockMax;
    p->mtc.alloc = &p->alignOffsetAlloc.vt;
      // p->alignOffsetAlloc.baseAlloc;
    // p->mtc.inData = inData;
    // p->mtc.inDataSize = inDataSize;
    p->mtc.mtCallback = &vt;
    p->mtc.mtCallbackObject = p;

    p->mtc.inBufSize = p->props.inBufSize_MT;

    p->mtc.numThreadsMax = p->props.numThreads;

    *isMT = True;

    vt.Parse = Lzma2DecMt_MtCallback_Parse;
    vt.PreCode = Lzma2DecMt_MtCallback_PreCode;
    vt.Code = Lzma2DecMt_MtCallback_Code;
    vt.Write = Lzma2DecMt_MtCallback_Write;

    {
      BoolInt needContinue = False;

      SRes res = MtDec_Code(&p->mtc);

      /*
      if (!outStream)
        *outBufSize = p->outBuf - outBuf;
      */

      *inProcessed = p->mtc.inProcessed;

      needContinue = False;

      if (res == SZ_OK)
      {
        if (p->mtc.mtProgress.res != SZ_OK)
          res = p->mtc.mtProgress.res;
        else
          needContinue = p->mtc.needContinue;
      }

      if (!needContinue)
      {
        if (res == SZ_OK)
          return p->mtc.readRes;
        return res;
      }

      tMode = True;
      p->readRes = p->mtc.readRes;
      p->readWasFinished = p->mtc.readWasFinished;
      p->inProcessed = p->mtc.inProcessed;
      
      PRF_STR("----- decoding ST -----");
    }
  }

  #endif


  *isMT = False;

  {
    SRes res = Lzma2Dec_Decode_ST(p
        #ifndef _7ZIP_ST
        , tMode
        #endif
        );

    *inProcessed = p->inProcessed;

    // res = SZ_OK; // for test
    if (res == SZ_OK && p->readRes != SZ_OK)
      res = p->readRes;
    
    /*
    #ifndef _7ZIP_ST
    if (res == SZ_OK && tMode && p->mtc.parseRes != SZ_OK)
      res = p->mtc.parseRes;
    #endif
    */
    
    return res;
  }
}