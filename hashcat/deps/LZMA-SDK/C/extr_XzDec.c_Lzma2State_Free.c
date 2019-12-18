#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  decoder; scalar_t__ outBufMode; } ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CLzma2Dec_Spec ;

/* Variables and functions */
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  Lzma2Dec_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lzma2Dec_FreeProbs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Lzma2State_Free(void *pp, ISzAllocPtr alloc)
{
  CLzma2Dec_Spec *p = (CLzma2Dec_Spec *)pp;
  if (p->outBufMode)
    Lzma2Dec_FreeProbs(&p->decoder, alloc);
  else
    Lzma2Dec_Free(&p->decoder, alloc);
  ISzAlloc_Free(alloc, pp);
}