#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  baseAlloc; } ;
struct TYPE_8__ {TYPE_1__ alignOffsetAlloc; TYPE_2__* coders; void* mtc_WasConstructed; int /*<<< orphan*/  mtc; } ;
struct TYPE_7__ {void* dec_created; int /*<<< orphan*/  dec; } ;
typedef  TYPE_2__ CXzDecMtThread ;
typedef  scalar_t__ CXzDecMtHandle ;
typedef  TYPE_3__ CXzDecMt ;

/* Variables and functions */
 void* False ; 
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int MTDEC__THREADS_MAX ; 
 int /*<<< orphan*/  MtDec_Destruct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XzDecMt_FreeOutBufs (TYPE_3__*) ; 
 int /*<<< orphan*/  XzDecMt_FreeSt (TYPE_3__*) ; 
 int /*<<< orphan*/  XzUnpacker_Free (int /*<<< orphan*/ *) ; 

void XzDecMt_Destroy(CXzDecMtHandle pp)
{
  CXzDecMt *p = (CXzDecMt *)pp;

  XzDecMt_FreeSt(p);

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
      CXzDecMtThread *t = &p->coders[i];
      if (t->dec_created)
      {
        // we don't need to free dict here
        XzUnpacker_Free(&t->dec);
        t->dec_created = False;
      }
    }
  }
  XzDecMt_FreeOutBufs(p);

  #endif

  ISzAlloc_Free(p->alignOffsetAlloc.baseAlloc, pp);
}