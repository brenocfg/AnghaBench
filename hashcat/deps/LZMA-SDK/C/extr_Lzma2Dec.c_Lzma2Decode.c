#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dicPos; int /*<<< orphan*/  dicBufSize; int /*<<< orphan*/ * dic; } ;
struct TYPE_9__ {TYPE_1__ decoder; } ;
typedef  int /*<<< orphan*/  SizeT ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  scalar_t__ ELzmaStatus ;
typedef  int /*<<< orphan*/  ELzmaFinishMode ;
typedef  TYPE_2__ CLzma2Dec ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ LZMA_STATUS_NEEDS_MORE_INPUT ; 
 scalar_t__ LZMA_STATUS_NOT_SPECIFIED ; 
 int /*<<< orphan*/  Lzma2Dec_AllocateProbs (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lzma2Dec_Construct (TYPE_2__*) ; 
 scalar_t__ Lzma2Dec_DecodeToDic (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  Lzma2Dec_FreeProbs (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lzma2Dec_Init (TYPE_2__*) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 scalar_t__ SZ_ERROR_INPUT_EOF ; 
 scalar_t__ SZ_OK ; 

SRes Lzma2Decode(Byte *dest, SizeT *destLen, const Byte *src, SizeT *srcLen,
    Byte prop, ELzmaFinishMode finishMode, ELzmaStatus *status, ISzAllocPtr alloc)
{
  CLzma2Dec p;
  SRes res;
  SizeT outSize = *destLen, inSize = *srcLen;
  *destLen = *srcLen = 0;
  *status = LZMA_STATUS_NOT_SPECIFIED;
  Lzma2Dec_Construct(&p);
  RINOK(Lzma2Dec_AllocateProbs(&p, prop, alloc));
  p.decoder.dic = dest;
  p.decoder.dicBufSize = outSize;
  Lzma2Dec_Init(&p);
  *srcLen = inSize;
  res = Lzma2Dec_DecodeToDic(&p, outSize, src, srcLen, finishMode, status);
  *destLen = p.decoder.dicPos;
  if (res == SZ_OK && *status == LZMA_STATUS_NEEDS_MORE_INPUT)
    res = SZ_ERROR_INPUT_EOF;
  Lzma2Dec_FreeProbs(&p, alloc);
  return res;
}