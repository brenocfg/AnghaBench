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
struct TYPE_5__ {scalar_t__ dicPos; } ;
struct TYPE_7__ {TYPE_1__ decoder; } ;
struct TYPE_6__ {TYPE_3__ decoder; scalar_t__ outBufMode; } ;
typedef  scalar_t__ SizeT ;
typedef  int /*<<< orphan*/  SRes ;
typedef  scalar_t__ ELzmaStatus ;
typedef  int /*<<< orphan*/  ELzmaFinishMode ;
typedef  scalar_t__ ECoderStatus ;
typedef  scalar_t__ ECoderFinishMode ;
typedef  TYPE_2__ CLzma2Dec_Spec ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  Lzma2Dec_DecodeToBuf (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/  const*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  Lzma2Dec_DecodeToDic (TYPE_3__*,scalar_t__,int /*<<< orphan*/  const*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  UNUSED_VAR (int) ; 

__attribute__((used)) static SRes Lzma2State_Code2(void *pp, Byte *dest, SizeT *destLen, const Byte *src, SizeT *srcLen,
    int srcWasFinished, ECoderFinishMode finishMode,
    // int *wasFinished,
    ECoderStatus *status)
{
  CLzma2Dec_Spec *spec = (CLzma2Dec_Spec *)pp;
  ELzmaStatus status2;
  /* ELzmaFinishMode fm = (finishMode == LZMA_FINISH_ANY) ? LZMA_FINISH_ANY : LZMA_FINISH_END; */
  SRes res;
  UNUSED_VAR(srcWasFinished);
  if (spec->outBufMode)
  {
    SizeT dicPos = spec->decoder.decoder.dicPos;
    SizeT dicLimit = dicPos + *destLen;
    res = Lzma2Dec_DecodeToDic(&spec->decoder, dicLimit, src, srcLen, (ELzmaFinishMode)finishMode, &status2);
    *destLen = spec->decoder.decoder.dicPos - dicPos;
  }
  else
    res = Lzma2Dec_DecodeToBuf(&spec->decoder, dest, destLen, src, srcLen, (ELzmaFinishMode)finishMode, &status2);
  // *wasFinished = (status2 == LZMA_STATUS_FINISHED_WITH_MARK);
  // ECoderStatus values are identical to ELzmaStatus values of LZMA2 decoder
  *status = (ECoderStatus)status2;
  return res;
}