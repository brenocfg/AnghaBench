#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  baseAlloc; } ;
struct TYPE_10__ {TYPE_2__ alignOffsetAlloc; TYPE_3__* coders; void* mtc_WasConstructed; int /*<<< orphan*/  mtc; } ;
struct TYPE_7__ {int /*<<< orphan*/  vt; } ;
struct TYPE_9__ {void* dec_created; TYPE_1__ alloc; int /*<<< orphan*/  dec; } ;
typedef  TYPE_3__ CLzma2DecMtThread ;
typedef  scalar_t__ CLzma2DecMtHandle ;
typedef  TYPE_4__ CLzma2DecMt ;

/* Variables and functions */
 void* False ; 
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  Lzma2DecMt_FreeOutBufs (TYPE_4__*) ; 
 int /*<<< orphan*/  Lzma2DecMt_FreeSt (TYPE_4__*) ; 
 int /*<<< orphan*/  Lzma2Dec_FreeProbs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int MTDEC__THREADS_MAX ; 
 int /*<<< orphan*/  MtDec_Destruct (int /*<<< orphan*/ *) ; 

void Lzma2DecMt_Destroy(CLzma2DecMtHandle pp)
{
  CLzma2DecMt *p = (CLzma2DecMt *)pp;

  Lzma2DecMt_FreeSt(p);

  #ifndef _7ZIP_ST

  if (p->mtc_WasConstructed)
  {
    MtDec_Destruct(&p->mtc);
    p->mtc_WasConstructed = False;
  }
  {
    unsigned i;
    for (i = 0; i < MTDEC__THREADS_MAX; i++)
    {
      CLzma2DecMtThread *t = &p->coders[i];
      if (t->dec_created)
      {
        // we don't need to free dict here
        Lzma2Dec_FreeProbs(&t->dec, &t->alloc.vt); // p->alloc !!!
        t->dec_created = False;
      }
    }
  }
  Lzma2DecMt_FreeOutBufs(p);

  #endif

  ISzAlloc_Free(p->alignOffsetAlloc.baseAlloc, pp);
}