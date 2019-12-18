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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  scalar_t__ e_FmPcdPlcrRateMode ;

/* Variables and functions */
 scalar_t__ e_FM_PCD_PLCR_BYTE_MODE ; 

__attribute__((used)) static void GetInfoRateReg(e_FmPcdPlcrRateMode  rateMode,
                           uint32_t             rate,
                           uint64_t             tsuInTenthNano,
                           uint32_t             fppShift,
                           uint64_t             *p_Integer,
                           uint64_t             *p_Fraction)
{
    uint64_t tmp, div;

    if (rateMode == e_FM_PCD_PLCR_BYTE_MODE)
    {
        /* now we calculate the initial integer for the bigger rate */
        /* from Kbps to Bytes/TSU */
        tmp = (uint64_t)rate;
        tmp *= 1000; /* kb --> b */
        tmp *= tsuInTenthNano; /* bps --> bpTsu(in 10nano) */

        div = 1000000000;   /* nano */
        div *= 10;          /* 10 nano */
        div *= 8;           /* bit to byte */
    }
    else
    {
        /* now we calculate the initial integer for the bigger rate */
        /* from Kbps to Bytes/TSU */
        tmp = (uint64_t)rate;
        tmp *= tsuInTenthNano; /* bps --> bpTsu(in 10nano) */

        div = 1000000000;   /* nano */
        div *= 10;          /* 10 nano */
    }
    *p_Integer = (tmp<<fppShift) / div;

    /* for calculating the fraction, we will recalculate cir and deduct the integer.
     * For precision, we will multiply by 2^16. we do not divid back, since we write
     * this value as fraction - see spec.
     */
    *p_Fraction = (((tmp<<fppShift)<<16) - ((*p_Integer<<16)*div)) / div;
}