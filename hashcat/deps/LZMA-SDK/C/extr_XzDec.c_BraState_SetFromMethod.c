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
typedef  scalar_t__ UInt64 ;
typedef  scalar_t__ UInt32 ;
struct TYPE_5__ {int encodeMode; scalar_t__ methodId; } ;
struct TYPE_4__ {int /*<<< orphan*/  Filter; int /*<<< orphan*/  Code2; int /*<<< orphan*/  Init; int /*<<< orphan*/  SetProps; int /*<<< orphan*/  Free; TYPE_2__* p; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ IStateCoder ;
typedef  TYPE_2__ CBraState ;

/* Variables and functions */
 int /*<<< orphan*/  BraState_Code2 ; 
 int /*<<< orphan*/  BraState_Filter ; 
 int /*<<< orphan*/  BraState_Free ; 
 int /*<<< orphan*/  BraState_Init ; 
 int /*<<< orphan*/  BraState_SetProps ; 
 scalar_t__ ISzAlloc_Alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_ERROR_UNSUPPORTED ; 
 int /*<<< orphan*/  SZ_OK ; 
 scalar_t__ XZ_ID_Delta ; 
 scalar_t__ XZ_ID_SPARC ; 

SRes BraState_SetFromMethod(IStateCoder *p, UInt64 id, int encodeMode, ISzAllocPtr alloc)
{
  CBraState *decoder;
  if (id < XZ_ID_Delta || id > XZ_ID_SPARC)
    return SZ_ERROR_UNSUPPORTED;
  decoder = (CBraState *)p->p;
  if (!decoder)
  {
    decoder = (CBraState *)ISzAlloc_Alloc(alloc, sizeof(CBraState));
    if (!decoder)
      return SZ_ERROR_MEM;
    p->p = decoder;
    p->Free = BraState_Free;
    p->SetProps = BraState_SetProps;
    p->Init = BraState_Init;
    p->Code2 = BraState_Code2;
    p->Filter = BraState_Filter;
  }
  decoder->methodId = (UInt32)id;
  decoder->encodeMode = encodeMode;
  return SZ_OK;
}