#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ dicBufSize; int /*<<< orphan*/ * dic; } ;
struct TYPE_10__ {TYPE_1__ decoder; } ;
struct TYPE_9__ {int /*<<< orphan*/  prop; int /*<<< orphan*/  allocMid; TYPE_3__* coders; } ;
struct TYPE_7__ {int /*<<< orphan*/  vt; } ;
struct TYPE_8__ {scalar_t__ inPreSize; scalar_t__ outBufSize; scalar_t__ outPreSize; TYPE_2__ alloc; TYPE_5__ dec; int /*<<< orphan*/  needInit; int /*<<< orphan*/ * outBuf; int /*<<< orphan*/  codeRes; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_3__ CLzma2DecMtThread ;
typedef  TYPE_4__ CLzma2DecMt ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ ISzAlloc_Alloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lzma2Dec_AllocateProbs (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SZ_ERROR_DATA ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  True ; 

__attribute__((used)) static SRes Lzma2DecMt_MtCallback_PreCode(void *pp, unsigned coderIndex)
{
  CLzma2DecMt *me = (CLzma2DecMt *)pp;
  CLzma2DecMtThread *t = &me->coders[coderIndex];
  Byte *dest = t->outBuf;

  if (t->inPreSize == 0)
  {
    t->codeRes = SZ_ERROR_DATA;
    return t->codeRes;
  }

  if (!dest || t->outBufSize < t->outPreSize)
  {
    if (dest)
    {
      ISzAlloc_Free(me->allocMid, dest);
      t->outBuf = NULL;
      t->outBufSize = 0;
    }

    dest = (Byte *)ISzAlloc_Alloc(me->allocMid, t->outPreSize
        // + (1 << 28)
        );
    // Sleep(200);
    if (!dest)
      return SZ_ERROR_MEM;
    t->outBuf = dest;
    t->outBufSize = t->outPreSize;
  }

  t->dec.decoder.dic = dest;
  t->dec.decoder.dicBufSize = t->outPreSize;

  t->needInit = True;

  return Lzma2Dec_AllocateProbs(&t->dec, me->prop, &t->alloc.vt); // alloc.vt
}