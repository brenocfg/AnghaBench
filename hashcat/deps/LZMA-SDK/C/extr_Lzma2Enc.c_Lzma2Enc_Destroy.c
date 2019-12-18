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
struct TYPE_5__ {int /*<<< orphan*/  alloc; int /*<<< orphan*/ * tempBufLzma; scalar_t__ mtCoder_WasConstructed; int /*<<< orphan*/  mtCoder; int /*<<< orphan*/  allocBig; TYPE_1__* coders; } ;
struct TYPE_4__ {int /*<<< orphan*/ * enc; } ;
typedef  TYPE_1__ CLzma2EncInt ;
typedef  int /*<<< orphan*/ * CLzma2EncHandle ;
typedef  TYPE_2__ CLzma2Enc ;

/* Variables and functions */
 scalar_t__ False ; 
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lzma2Enc_FreeOutBufs (TYPE_2__*) ; 
 int /*<<< orphan*/  LzmaEnc_Destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int MTCODER__THREADS_MAX ; 
 int /*<<< orphan*/  MtCoder_Destruct (int /*<<< orphan*/ *) ; 

void Lzma2Enc_Destroy(CLzma2EncHandle pp)
{
  CLzma2Enc *p = (CLzma2Enc *)pp;
  unsigned i;
  for (i = 0; i < MTCODER__THREADS_MAX; i++)
  {
    CLzma2EncInt *t = &p->coders[i];
    if (t->enc)
    {
      LzmaEnc_Destroy(t->enc, p->alloc, p->allocBig);
      t->enc = NULL;
    }
  }


  #ifndef _7ZIP_ST
  if (p->mtCoder_WasConstructed)
  {
    MtCoder_Destruct(&p->mtCoder);
    p->mtCoder_WasConstructed = False;
  }
  Lzma2Enc_FreeOutBufs(p);
  #endif

  ISzAlloc_Free(p->alloc, p->tempBufLzma);
  p->tempBufLzma = NULL;

  ISzAlloc_Free(p->alloc, pp);
}