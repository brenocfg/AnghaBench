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
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CLzma2Dec_Spec ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  Lzma2Dec_Allocate (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lzma2Dec_AllocateProbs (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_UNSUPPORTED ; 

__attribute__((used)) static SRes Lzma2State_SetProps(void *pp, const Byte *props, size_t propSize, ISzAllocPtr alloc)
{
  if (propSize != 1)
    return SZ_ERROR_UNSUPPORTED;
  {
    CLzma2Dec_Spec *p = (CLzma2Dec_Spec *)pp;
    if (p->outBufMode)
      return Lzma2Dec_AllocateProbs(&p->decoder, props[0], alloc);
    else
      return Lzma2Dec_Allocate(&p->decoder, props[0], alloc);
  }
}