#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int numAlignBits; int /*<<< orphan*/  vt; scalar_t__ offset; void* baseAlloc; } ;
struct TYPE_7__ {TYPE_1__* coders; void* mtc_WasConstructed; int /*<<< orphan*/  props; scalar_t__ unpackBlockMaxSize; TYPE_5__ alignOffsetAlloc; int /*<<< orphan*/  dec; scalar_t__ inBufSize; int /*<<< orphan*/ * inBuf; scalar_t__ outBufSize; int /*<<< orphan*/ * outBuf; void* allocMid; } ;
struct TYPE_6__ {scalar_t__ outBufSize; int /*<<< orphan*/ * outBuf; void* dec_created; } ;
typedef  void* ISzAllocPtr ;
typedef  TYPE_1__ CXzDecMtThread ;
typedef  TYPE_2__* CXzDecMtHandle ;
typedef  TYPE_2__ CXzDecMt ;

/* Variables and functions */
 int /*<<< orphan*/  AlignOffsetAlloc_CreateVTable (TYPE_5__*) ; 
 void* False ; 
 scalar_t__ ISzAlloc_Alloc (void*,int) ; 
 unsigned int MTDEC__THREADS_MAX ; 
 int /*<<< orphan*/  XzDecMtProps_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XzUnpacker_Construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

CXzDecMtHandle XzDecMt_Create(ISzAllocPtr alloc, ISzAllocPtr allocMid)
{
  CXzDecMt *p = (CXzDecMt *)ISzAlloc_Alloc(alloc, sizeof(CXzDecMt));
  if (!p)
    return NULL;
  
  AlignOffsetAlloc_CreateVTable(&p->alignOffsetAlloc);
  p->alignOffsetAlloc.baseAlloc = alloc;
  p->alignOffsetAlloc.numAlignBits = 7;
  p->alignOffsetAlloc.offset = 0;

  p->allocMid = allocMid;

  p->outBuf = NULL;
  p->outBufSize = 0;
  p->inBuf = NULL;
  p->inBufSize = 0;

  XzUnpacker_Construct(&p->dec, &p->alignOffsetAlloc.vt);

  p->unpackBlockMaxSize = 0;

  XzDecMtProps_Init(&p->props);

  #ifndef _7ZIP_ST
  p->mtc_WasConstructed = False;
  {
    unsigned i;
    for (i = 0; i < MTDEC__THREADS_MAX; i++)
    {
      CXzDecMtThread *coder = &p->coders[i];
      coder->dec_created = False;
      coder->outBuf = NULL;
      coder->outBufSize = 0;
    }
  }
  #endif

  return p;
}