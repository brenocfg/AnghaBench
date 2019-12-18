#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t dicBufSize; int /*<<< orphan*/ * dic; } ;
struct TYPE_9__ {TYPE_1__ decoder; } ;
struct TYPE_8__ {TYPE_5__ decoder; int /*<<< orphan*/  outBufMode; } ;
struct TYPE_7__ {int /*<<< orphan*/ * Filter; int /*<<< orphan*/  Code2; int /*<<< orphan*/  Init; int /*<<< orphan*/  SetProps; int /*<<< orphan*/  Free; TYPE_3__* p; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_2__ IStateCoder ;
typedef  TYPE_3__ CLzma2Dec_Spec ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 scalar_t__ ISzAlloc_Alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Lzma2Dec_Construct (TYPE_5__*) ; 
 int /*<<< orphan*/  Lzma2State_Code2 ; 
 int /*<<< orphan*/  Lzma2State_Free ; 
 int /*<<< orphan*/  Lzma2State_Init ; 
 int /*<<< orphan*/  Lzma2State_SetProps ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  True ; 

__attribute__((used)) static SRes Lzma2State_SetFromMethod(IStateCoder *p, Byte *outBuf, size_t outBufSize, ISzAllocPtr alloc)
{
  CLzma2Dec_Spec *spec = (CLzma2Dec_Spec *)p->p;
  if (!spec)
  {
    spec = (CLzma2Dec_Spec *)ISzAlloc_Alloc(alloc, sizeof(CLzma2Dec_Spec));
    if (!spec)
      return SZ_ERROR_MEM;
    p->p = spec;
    p->Free = Lzma2State_Free;
    p->SetProps = Lzma2State_SetProps;
    p->Init = Lzma2State_Init;
    p->Code2 = Lzma2State_Code2;
    p->Filter = NULL;
    Lzma2Dec_Construct(&spec->decoder);
  }
  spec->outBufMode = False;
  if (outBuf)
  {
    spec->outBufMode = True;
    spec->decoder.decoder.dic = outBuf;
    spec->decoder.decoder.dicBufSize = outBufSize;
  }
  return SZ_OK;
}