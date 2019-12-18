#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt64 ;
struct TYPE_6__ {scalar_t__ outBufSize; int /*<<< orphan*/ ** outBufs; int /*<<< orphan*/  mtCoder_WasConstructed; TYPE_1__* coders; void* allocBig; void* alloc; int /*<<< orphan*/ * tempBufLzma; scalar_t__ expectedDataSize; int /*<<< orphan*/  props; } ;
struct TYPE_5__ {int /*<<< orphan*/ * enc; } ;
typedef  scalar_t__ Int64 ;
typedef  void* ISzAllocPtr ;
typedef  TYPE_2__* CLzma2EncHandle ;
typedef  TYPE_2__ CLzma2Enc ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 scalar_t__ ISzAlloc_Alloc (void*,int) ; 
 int /*<<< orphan*/  Lzma2EncProps_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lzma2EncProps_Normalize (int /*<<< orphan*/ *) ; 
 unsigned int MTCODER__BLOCKS_MAX ; 
 unsigned int MTCODER__THREADS_MAX ; 

CLzma2EncHandle Lzma2Enc_Create(ISzAllocPtr alloc, ISzAllocPtr allocBig)
{
  CLzma2Enc *p = (CLzma2Enc *)ISzAlloc_Alloc(alloc, sizeof(CLzma2Enc));
  if (!p)
    return NULL;
  Lzma2EncProps_Init(&p->props);
  Lzma2EncProps_Normalize(&p->props);
  p->expectedDataSize = (UInt64)(Int64)-1;
  p->tempBufLzma = NULL;
  p->alloc = alloc;
  p->allocBig = allocBig;
  {
    unsigned i;
    for (i = 0; i < MTCODER__THREADS_MAX; i++)
      p->coders[i].enc = NULL;
  }
  
  #ifndef _7ZIP_ST
  p->mtCoder_WasConstructed = False;
  {
    unsigned i;
    for (i = 0; i < MTCODER__BLOCKS_MAX; i++)
      p->outBufs[i] = NULL;
    p->outBufSize = 0;
  }
  #endif

  return p;
}