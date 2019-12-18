#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  block; int /*<<< orphan*/  decoder; int /*<<< orphan*/  headerParsedOk; } ;
struct TYPE_5__ {scalar_t__ ignoreErrors; } ;
struct TYPE_7__ {size_t unpackBlockMaxSize; TYPE_1__ props; int /*<<< orphan*/  allocMid; TYPE_2__* coders; } ;
struct TYPE_6__ {size_t outBufSize; size_t outPreSize; scalar_t__ codeRes; int /*<<< orphan*/ * outBuf; TYPE_4__ dec; } ;
typedef  scalar_t__ SRes ;
typedef  TYPE_2__ CXzDecMtThread ;
typedef  TYPE_3__ CXzDecMt ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ ISzAlloc_Alloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SZ_ERROR_MEM ; 
 scalar_t__ SZ_OK ; 
 scalar_t__ S_OK ; 
 scalar_t__ XzDecMix_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  XzUnpacker_SetOutBuf (TYPE_4__*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static SRes XzDecMt_Callback_PreCode(void *pp, unsigned coderIndex)
{
  CXzDecMt *me = (CXzDecMt *)pp;
  CXzDecMtThread *coder = &me->coders[coderIndex];
  Byte *dest;

  if (!coder->dec.headerParsedOk)
    return SZ_OK;

  dest = coder->outBuf;

  if (!dest || coder->outBufSize < coder->outPreSize)
  {
    if (dest)
    {
      ISzAlloc_Free(me->allocMid, dest);
      coder->outBuf = NULL;
      coder->outBufSize = 0;
    }
    {
      size_t outPreSize = coder->outPreSize;
      if (outPreSize == 0)
        outPreSize = 1;
      dest = (Byte *)ISzAlloc_Alloc(me->allocMid, outPreSize);
    }
    if (!dest)
      return SZ_ERROR_MEM;
    coder->outBuf = dest;
    coder->outBufSize = coder->outPreSize;

    if (coder->outBufSize > me->unpackBlockMaxSize)
      me->unpackBlockMaxSize = coder->outBufSize;
  }

  // return SZ_ERROR_MEM;

  XzUnpacker_SetOutBuf(&coder->dec, coder->outBuf, coder->outBufSize);

  {
    SRes res = XzDecMix_Init(&coder->dec.decoder, &coder->dec.block, coder->outBuf, coder->outBufSize);
    // res = SZ_ERROR_UNSUPPORTED; // to test
    coder->codeRes = res;
    if (res != SZ_OK)
    {
      // if (res == SZ_ERROR_MEM) return res;
      if (me->props.ignoreErrors && res != SZ_ERROR_MEM)
        return S_OK;
      return res;
    }
  }

  return SZ_OK;
}