#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ UInt64 ;
struct TYPE_18__ {int /*<<< orphan*/  Progress; } ;
struct TYPE_17__ {scalar_t__ outOffset; scalar_t__ inOffset; TYPE_7__ vt; int /*<<< orphan*/ * progress; } ;
struct TYPE_12__ {size_t blockSize; int /*<<< orphan*/  expectedDataSize; int /*<<< orphan*/  numThreadsMax; TYPE_4__* mtCallbackObject; TYPE_1__* mtCallback; scalar_t__ inDataSize; int /*<<< orphan*/ * inData; int /*<<< orphan*/ * inStream; int /*<<< orphan*/ * progress; int /*<<< orphan*/  allocBig; } ;
struct TYPE_14__ {scalar_t__ blockSize; scalar_t__ reduceSize; int numBlockThreads_Reduced; scalar_t__ forceWriteSizesInHeader; scalar_t__ checkId; int /*<<< orphan*/  numBlockThreads_Max; } ;
struct TYPE_16__ {size_t outBufSize; int /*<<< orphan*/  xzIndex; int /*<<< orphan*/  alloc; int /*<<< orphan*/ ** outBufs; int /*<<< orphan*/  allocBig; int /*<<< orphan*/ * lzmaf_Items; TYPE_10__ mtCoder; int /*<<< orphan*/  expectedDataSize; int /*<<< orphan*/ * outStream; TYPE_2__ xzProps; scalar_t__ checkType; scalar_t__ mtCoder_WasConstructed; } ;
struct TYPE_15__ {scalar_t__ totalSize; scalar_t__ unpackSize; scalar_t__ headerSize; } ;
struct TYPE_13__ {int /*<<< orphan*/  Write; int /*<<< orphan*/  Code; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  scalar_t__ Int64 ;
typedef  int /*<<< orphan*/  ISeqOutStream ;
typedef  int /*<<< orphan*/  ISeqInStream ;
typedef  TYPE_1__ IMtCoderCallback2 ;
typedef  int /*<<< orphan*/  ICompressProgress ;
typedef  int /*<<< orphan*/  CXzStreamFlags ;
typedef  TYPE_2__ CXzProps ;
typedef  scalar_t__ CXzEncHandle ;
typedef  TYPE_3__ CXzEncBlockInfo ;
typedef  TYPE_4__ CXzEnc ;
typedef  TYPE_5__ CCompressProgress_XzEncOffset ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  CompressProgress_XzEncOffset_Progress ; 
 scalar_t__ ISzAlloc_Alloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  MtCoder_Code (TYPE_10__*) ; 
 int /*<<< orphan*/  MtCoder_Construct (TYPE_10__*) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_FAIL ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_ERROR_PARAM ; 
 scalar_t__ True ; 
 int /*<<< orphan*/  WriteBytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 size_t XZ_BLOCK_HEADER_SIZE_MAX ; 
 int /*<<< orphan*/  XZ_GET_ESTIMATED_BLOCK_TOTAL_PACK_SIZE (scalar_t__) ; 
 size_t XZ_GET_MAX_BLOCK_PACK_SIZE (size_t) ; 
 scalar_t__ XZ_GET_PAD_SIZE (scalar_t__) ; 
 scalar_t__ XZ_PROPS__BLOCK_SIZE__AUTO ; 
 scalar_t__ XZ_PROPS__BLOCK_SIZE__SOLID ; 
 int /*<<< orphan*/  XzEncIndex_AddIndexRecord (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XzEncIndex_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XzEncIndex_PreAlloc (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XzEncIndex_WriteFooter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XzEnc_FreeOutBufs (TYPE_4__*) ; 
 int /*<<< orphan*/  XzEnc_MtCallback_Code ; 
 int /*<<< orphan*/  XzEnc_MtCallback_Write ; 
 int /*<<< orphan*/  Xz_CompressBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__ const*,TYPE_7__*,int*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Xz_WriteHeader (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

SRes XzEnc_Encode(CXzEncHandle pp, ISeqOutStream *outStream, ISeqInStream *inStream, ICompressProgress *progress)
{
  CXzEnc *p = (CXzEnc *)pp;

  const CXzProps *props = &p->xzProps;

  XzEncIndex_Init(&p->xzIndex);
  {
    UInt64 numBlocks = 1;
    UInt64 blockSize = props->blockSize;
    
    if (blockSize != XZ_PROPS__BLOCK_SIZE__SOLID
        && props->reduceSize != (UInt64)(Int64)-1)
    {
      numBlocks = props->reduceSize / blockSize;
      if (numBlocks * blockSize != props->reduceSize)
        numBlocks++;
    }
    else
      blockSize = (UInt64)1 << 62;
    
    RINOK(XzEncIndex_PreAlloc(&p->xzIndex, numBlocks, blockSize, XZ_GET_ESTIMATED_BLOCK_TOTAL_PACK_SIZE(blockSize), p->alloc));
  }

  RINOK(Xz_WriteHeader((CXzStreamFlags)props->checkId, outStream));


  #ifndef _7ZIP_ST
  if (props->numBlockThreads_Reduced > 1)
  {
    IMtCoderCallback2 vt;

    if (!p->mtCoder_WasConstructed)
    {
      p->mtCoder_WasConstructed = True;
      MtCoder_Construct(&p->mtCoder);
    }

    vt.Code = XzEnc_MtCallback_Code;
    vt.Write = XzEnc_MtCallback_Write;

    p->checkType = props->checkId;
    p->xzProps = *props;
    
    p->outStream = outStream;

    p->mtCoder.allocBig = p->allocBig;
    p->mtCoder.progress = progress;
    p->mtCoder.inStream = inStream;
    p->mtCoder.inData = NULL;
    p->mtCoder.inDataSize = 0;
    p->mtCoder.mtCallback = &vt;
    p->mtCoder.mtCallbackObject = p;

    if (   props->blockSize == XZ_PROPS__BLOCK_SIZE__SOLID
        || props->blockSize == XZ_PROPS__BLOCK_SIZE__AUTO)
      return SZ_ERROR_FAIL;

    p->mtCoder.blockSize = (size_t)props->blockSize;
    if (p->mtCoder.blockSize != props->blockSize)
      return SZ_ERROR_PARAM; /* SZ_ERROR_MEM */

    {
      size_t destBlockSize = XZ_BLOCK_HEADER_SIZE_MAX + XZ_GET_MAX_BLOCK_PACK_SIZE(p->mtCoder.blockSize);
      if (destBlockSize < p->mtCoder.blockSize)
        return SZ_ERROR_PARAM;
      if (p->outBufSize != destBlockSize)
        XzEnc_FreeOutBufs(p);
      p->outBufSize = destBlockSize;
    }

    p->mtCoder.numThreadsMax = props->numBlockThreads_Max;
    p->mtCoder.expectedDataSize = p->expectedDataSize;
    
    RINOK(MtCoder_Code(&p->mtCoder));
  }
  else
  #endif
  {
    int writeStartSizes;
    CCompressProgress_XzEncOffset progress2;
    Byte *bufData = NULL;
    size_t bufSize = 0;

    progress2.vt.Progress = CompressProgress_XzEncOffset_Progress;
    progress2.inOffset = 0;
    progress2.outOffset = 0;
    progress2.progress = progress;
    
    writeStartSizes = 0;
    
    if (props->blockSize != XZ_PROPS__BLOCK_SIZE__SOLID)
    {
      writeStartSizes = (props->forceWriteSizesInHeader > 0);
      
      if (writeStartSizes)
      {
        size_t t2;
        size_t t = (size_t)props->blockSize;
        if (t != props->blockSize)
          return SZ_ERROR_PARAM;
        t = XZ_GET_MAX_BLOCK_PACK_SIZE(t);
        if (t < props->blockSize)
          return SZ_ERROR_PARAM;
        t2 = XZ_BLOCK_HEADER_SIZE_MAX + t;
        if (!p->outBufs[0] || t2 != p->outBufSize)
        {
          XzEnc_FreeOutBufs(p);
          p->outBufs[0] = (Byte *)ISzAlloc_Alloc(p->alloc, t2);
          if (!p->outBufs[0])
            return SZ_ERROR_MEM;
          p->outBufSize = t2;
        }
        bufData = p->outBufs[0] + XZ_BLOCK_HEADER_SIZE_MAX;
        bufSize = t;
      }
    }
    
    for (;;)
    {
      CXzEncBlockInfo blockSizes;
      int inStreamFinished;
      
      /*
      UInt64 rem = (UInt64)(Int64)-1;
      if (props->reduceSize != (UInt64)(Int64)-1
          && props->reduceSize >= progress2.inOffset)
        rem = props->reduceSize - progress2.inOffset;
      */

      blockSizes.headerSize = 0; // for GCC
      
      RINOK(Xz_CompressBlock(
          &p->lzmaf_Items[0],
          
          writeStartSizes ? NULL : outStream,
          writeStartSizes ? p->outBufs[0] : NULL,
          bufData, bufSize,
          
          inStream,
          // rem,
          NULL, 0,
          
          props,
          progress ? &progress2.vt : NULL,
          &inStreamFinished,
          &blockSizes,
          p->alloc,
          p->allocBig));

      {
        UInt64 totalPackFull = blockSizes.totalSize + XZ_GET_PAD_SIZE(blockSizes.totalSize);
      
        if (writeStartSizes)
        {
          RINOK(WriteBytes(outStream, p->outBufs[0], blockSizes.headerSize));
          RINOK(WriteBytes(outStream, bufData, (size_t)totalPackFull - blockSizes.headerSize));
        }
        
        RINOK(XzEncIndex_AddIndexRecord(&p->xzIndex, blockSizes.unpackSize, blockSizes.totalSize, p->alloc));
        
        progress2.inOffset += blockSizes.unpackSize;
        progress2.outOffset += totalPackFull;
      }
        
      if (inStreamFinished)
        break;
    }
  }

  return XzEncIndex_WriteFooter(&p->xzIndex, (CXzStreamFlags)props->checkId, outStream);
}