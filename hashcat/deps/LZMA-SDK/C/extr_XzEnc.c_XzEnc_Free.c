#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mtCoder_WasConstructed; int /*<<< orphan*/  mtCoder; int /*<<< orphan*/ * lzmaf_Items; int /*<<< orphan*/  xzIndex; } ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CXzEnc ;

/* Variables and functions */
 scalar_t__ False ; 
 int /*<<< orphan*/  Lzma2WithFilters_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int MTCODER__THREADS_MAX ; 
 int /*<<< orphan*/  MtCoder_Destruct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XzEncIndex_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XzEnc_FreeOutBufs (TYPE_1__*) ; 

__attribute__((used)) static void XzEnc_Free(CXzEnc *p, ISzAllocPtr alloc)
{
  unsigned i;

  XzEncIndex_Free(&p->xzIndex, alloc);

  for (i = 0; i < MTCODER__THREADS_MAX; i++)
    Lzma2WithFilters_Free(&p->lzmaf_Items[i], alloc);
  
  #ifndef _7ZIP_ST
  if (p->mtCoder_WasConstructed)
  {
    MtCoder_Destruct(&p->mtCoder);
    p->mtCoder_WasConstructed = False;
  }
  XzEnc_FreeOutBufs(p);
  #endif
}