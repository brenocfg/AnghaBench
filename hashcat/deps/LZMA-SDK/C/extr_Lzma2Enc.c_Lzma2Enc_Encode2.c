#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  propsAreSet; } ;
struct TYPE_12__ {size_t inDataSize; size_t blockSize; int /*<<< orphan*/  expectedDataSize; int /*<<< orphan*/  numThreadsMax; TYPE_3__* mtCallbackObject; TYPE_2__* mtCallback; int /*<<< orphan*/  const* inData; int /*<<< orphan*/ * inStream; int /*<<< orphan*/ * progress; int /*<<< orphan*/  allocBig; } ;
struct TYPE_9__ {int numBlockThreads_Reduced; size_t blockSize; int /*<<< orphan*/  numBlockThreads_Max; } ;
struct TYPE_11__ {size_t outBuf_Rem; size_t outBufSize; TYPE_8__* coders; int /*<<< orphan*/ * outBuf; TYPE_4__ mtCoder; int /*<<< orphan*/  expectedDataSize; TYPE_1__ props; int /*<<< orphan*/  allocBig; int /*<<< orphan*/ * outStream; scalar_t__ mtCoder_WasConstructed; } ;
struct TYPE_10__ {int /*<<< orphan*/  Write; int /*<<< orphan*/  Code; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISeqOutStream ;
typedef  int /*<<< orphan*/  ISeqInStream ;
typedef  TYPE_2__ IMtCoderCallback2 ;
typedef  int /*<<< orphan*/  ICompressProgress ;
typedef  scalar_t__ CLzma2EncHandle ;
typedef  TYPE_3__ CLzma2Enc ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  Lzma2Enc_EncodeMt1 (TYPE_3__*,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lzma2Enc_FreeOutBufs (TYPE_3__*) ; 
 int /*<<< orphan*/  Lzma2Enc_MtCallback_Code ; 
 int /*<<< orphan*/  Lzma2Enc_MtCallback_Write ; 
 unsigned int MTCODER__THREADS_MAX ; 
 int /*<<< orphan*/  MtCoder_Code (TYPE_4__*) ; 
 int /*<<< orphan*/  MtCoder_Construct (TYPE_4__*) ; 
 int /*<<< orphan*/  SZ_ERROR_PARAM ; 
 scalar_t__ True ; 

SRes Lzma2Enc_Encode2(CLzma2EncHandle pp,
    ISeqOutStream *outStream,
    Byte *outBuf, size_t *outBufSize,
    ISeqInStream *inStream,
    const Byte *inData, size_t inDataSize,
    ICompressProgress *progress)
{
  CLzma2Enc *p = (CLzma2Enc *)pp;

  if (inStream && inData)
    return SZ_ERROR_PARAM;

  if (outStream && outBuf)
    return SZ_ERROR_PARAM;

  {
    unsigned i;
    for (i = 0; i < MTCODER__THREADS_MAX; i++)
      p->coders[i].propsAreSet = False;
  }

  #ifndef _7ZIP_ST
  
  if (p->props.numBlockThreads_Reduced > 1)
  {
    IMtCoderCallback2 vt;

    if (!p->mtCoder_WasConstructed)
    {
      p->mtCoder_WasConstructed = True;
      MtCoder_Construct(&p->mtCoder);
    }

    vt.Code = Lzma2Enc_MtCallback_Code;
    vt.Write = Lzma2Enc_MtCallback_Write;

    p->outStream = outStream;
    p->outBuf = NULL;
    p->outBuf_Rem = 0;
    if (!outStream)
    {
      p->outBuf = outBuf;
      p->outBuf_Rem = *outBufSize;
      *outBufSize = 0;
    }

    p->mtCoder.allocBig = p->allocBig;
    p->mtCoder.progress = progress;
    p->mtCoder.inStream = inStream;
    p->mtCoder.inData = inData;
    p->mtCoder.inDataSize = inDataSize;
    p->mtCoder.mtCallback = &vt;
    p->mtCoder.mtCallbackObject = p;

    p->mtCoder.blockSize = (size_t)p->props.blockSize;
    if (p->mtCoder.blockSize != p->props.blockSize)
      return SZ_ERROR_PARAM; /* SZ_ERROR_MEM */

    {
      size_t destBlockSize = p->mtCoder.blockSize + (p->mtCoder.blockSize >> 10) + 16;
      if (destBlockSize < p->mtCoder.blockSize)
        return SZ_ERROR_PARAM;
      if (p->outBufSize != destBlockSize)
        Lzma2Enc_FreeOutBufs(p);
      p->outBufSize = destBlockSize;
    }

    p->mtCoder.numThreadsMax = p->props.numBlockThreads_Max;
    p->mtCoder.expectedDataSize = p->expectedDataSize;
    
    {
      SRes res = MtCoder_Code(&p->mtCoder);
      if (!outStream)
        *outBufSize = p->outBuf - outBuf;
      return res;
    }
  }

  #endif


  return Lzma2Enc_EncodeMt1(p,
      &p->coders[0],
      outStream, outBuf, outBufSize,
      inStream, inData, inDataSize,
      True, /* finished */
      progress);
}