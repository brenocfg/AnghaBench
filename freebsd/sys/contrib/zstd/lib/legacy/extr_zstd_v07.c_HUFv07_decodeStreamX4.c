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
typedef  int /*<<< orphan*/  HUFv07_DEltX4 ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BITv07_DStream_t ;

/* Variables and functions */
 scalar_t__ BITv07_DStream_unfinished ; 
 scalar_t__ BITv07_reloadDStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HUFv07_DECODE_SYMBOLX4_0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HUFv07_DECODE_SYMBOLX4_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HUFv07_DECODE_SYMBOLX4_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HUFv07_decodeLastSymbolX4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline size_t HUFv07_decodeStreamX4(BYTE* p, BITv07_DStream_t* bitDPtr, BYTE* const pEnd, const HUFv07_DEltX4* const dt, const U32 dtLog)
{
    BYTE* const pStart = p;

    /* up to 8 symbols at a time */
    while ((BITv07_reloadDStream(bitDPtr) == BITv07_DStream_unfinished) && (p < pEnd-7)) {
        HUFv07_DECODE_SYMBOLX4_2(p, bitDPtr);
        HUFv07_DECODE_SYMBOLX4_1(p, bitDPtr);
        HUFv07_DECODE_SYMBOLX4_2(p, bitDPtr);
        HUFv07_DECODE_SYMBOLX4_0(p, bitDPtr);
    }

    /* closer to end : up to 2 symbols at a time */
    while ((BITv07_reloadDStream(bitDPtr) == BITv07_DStream_unfinished) && (p <= pEnd-2))
        HUFv07_DECODE_SYMBOLX4_0(p, bitDPtr);

    while (p <= pEnd-2)
        HUFv07_DECODE_SYMBOLX4_0(p, bitDPtr);   /* no need to reload : reached the end of DStream */

    if (p < pEnd)
        p += HUFv07_decodeLastSymbolX4(p, bitDPtr, dt, dtLog);

    return p-pStart;
}