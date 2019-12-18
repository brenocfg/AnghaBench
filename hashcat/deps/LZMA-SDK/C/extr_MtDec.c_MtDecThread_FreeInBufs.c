#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* next; } ;
struct TYPE_6__ {TYPE_1__* mtDec; int /*<<< orphan*/ * inBuf; } ;
struct TYPE_5__ {int /*<<< orphan*/  alloc; } ;
typedef  TYPE_2__ CMtDecThread ;
typedef  TYPE_3__ CMtDecBufLink ;

/* Variables and functions */
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,void*) ; 

void MtDecThread_FreeInBufs(CMtDecThread *t)
{
  if (t->inBuf)
  {
    void *link = t->inBuf;
    t->inBuf = NULL;
    do
    {
      void *next = ((CMtDecBufLink *)link)->next;
      ISzAlloc_Free(t->mtDec->alloc, link);
      link = next;
    }
    while (link);
  }
}