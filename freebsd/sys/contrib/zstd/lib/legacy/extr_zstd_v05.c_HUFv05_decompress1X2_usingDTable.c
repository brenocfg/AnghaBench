#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  U16 ;
typedef  int /*<<< orphan*/  HUFv05_DEltX2 ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BITv05_DStream_t ;

/* Variables and functions */
 int /*<<< orphan*/  BITv05_endOfDStream (int /*<<< orphan*/ *) ; 
 size_t BITv05_initDStream (int /*<<< orphan*/ *,void const*,size_t) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUFv05_decodeStreamX2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const) ; 
 scalar_t__ HUFv05_isError (size_t const) ; 
 int /*<<< orphan*/  corruption_detected ; 
 int /*<<< orphan*/  dstSize_tooSmall ; 

size_t HUFv05_decompress1X2_usingDTable(
          void* dst,  size_t dstSize,
    const void* cSrc, size_t cSrcSize,
    const U16* DTable)
{
    BYTE* op = (BYTE*)dst;
    BYTE* const oend = op + dstSize;
    const U32 dtLog = DTable[0];
    const void* dtPtr = DTable;
    const HUFv05_DEltX2* const dt = ((const HUFv05_DEltX2*)dtPtr)+1;
    BITv05_DStream_t bitD;

    if (dstSize <= cSrcSize) return ERROR(dstSize_tooSmall);
    { size_t const errorCode = BITv05_initDStream(&bitD, cSrc, cSrcSize);
      if (HUFv05_isError(errorCode)) return errorCode; }

    HUFv05_decodeStreamX2(op, &bitD, oend, dt, dtLog);

    /* check */
    if (!BITv05_endOfDStream(&bitD)) return ERROR(corruption_detected);

    return dstSize;
}