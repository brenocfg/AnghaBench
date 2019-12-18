#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ committedInfoRate; scalar_t__ peakOrExcessInfoRate; int committedBurstSize; int peakOrExcessBurstSize; int /*<<< orphan*/  rateMode; } ;
typedef  TYPE_1__ t_FmPcdPlcrNonPassthroughAlgParams ;

/* Variables and functions */
 int CalcFPP (int) ; 
 int /*<<< orphan*/  E_INVALID_SELECTION ; 
 int /*<<< orphan*/  GetInfoRateReg (int /*<<< orphan*/ ,scalar_t__,int,int,int*,int*) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void CalcRates(uint32_t                              bitFor1Micro,
                      t_FmPcdPlcrNonPassthroughAlgParams    *p_NonPassthroughAlgParam,
                      uint32_t                              *cir,
                      uint32_t                              *cbs,
                      uint32_t                              *pir_eir,
                      uint32_t                              *pbs_ebs,
                      uint32_t                              *fpp)
{
    uint64_t    integer, fraction;
    uint32_t    temp, tsuInTenthNanos;
    uint8_t     fppShift=0;

    /* we want the tsu to count 10 nano for better precision normally tsu is 3.9 nano, now we will get 39 */
    tsuInTenthNanos = (uint32_t)(1000*10/(1 << bitFor1Micro));

    /* we choose the faster rate to calibrate fpp */
    /* The meaning of this step:
     * when fppShift is 0 it means all TS bits are treated as integer and TSU is the TS LSB count.
     * In this configuration we calculate the integer and fraction that represent the higher infoRate
     * When this is done, we can tell where we have "spare" unused bits and optimize the division of TS
     * into "integer" and "fraction" where the logic is - as many bits as possible for integer at
     * high rate, as many bits as possible for fraction at low rate.
     */
    if (p_NonPassthroughAlgParam->committedInfoRate > p_NonPassthroughAlgParam->peakOrExcessInfoRate)
        GetInfoRateReg(p_NonPassthroughAlgParam->rateMode, p_NonPassthroughAlgParam->committedInfoRate, tsuInTenthNanos, 0, &integer, &fraction);
    else
        GetInfoRateReg(p_NonPassthroughAlgParam->rateMode, p_NonPassthroughAlgParam->peakOrExcessInfoRate, tsuInTenthNanos, 0, &integer, &fraction);

    /* we shift integer, as in cir/pir it is represented by the MSB 16 bits, and
     * the LSB bits are for the fraction */
    temp = (uint32_t)((integer<<16) & 0x00000000FFFFFFFF);
    /* temp is effected by the rate. For low rates it may be as low as 0, and then we'll
     * take max FP = 31.
     * For high rates it will never exceed the 32 bit reg (after the 16 shift), as it is
     * limited by the 10G physical port.
     */
    if (temp != 0)
    {
        /* In this case, the largest rate integer is non 0, if it does not occupy all (high) 16
         * bits of the PIR_EIR we can use this fact and enlarge it to occupy all 16 bits.
         * The logic is to have as many bits for integer in the higher rates, but if we have "0"s
         * in the integer part of the cir/pir register, than these bits are wasted. So we want
         * to use these bits for the fraction. in this way we will have for fraction - the number
         * of "0" bits and the rest - for integer.
         * In other words: For each bit we shift it in PIR_EIR, we move the FP in the TS
         * one bit to the left - preserving the relationship and achieving more bits
         * for integer in the TS.
         */

        /* count zeroes left of the higher used bit (in order to shift the value such that
         * unused bits may be used for fraction).
         */
        while ((temp & 0x80000000) == 0)
        {
            temp = temp << 1;
            fppShift++;
        }
        if (fppShift > 15)
        {
            REPORT_ERROR(MAJOR, E_INVALID_SELECTION, ("timeStampPeriod to Information rate ratio is too small"));
            return;
        }
    }
    else
    {
        temp = (uint32_t)fraction; /* fraction will alyas be smaller than 2^16 */
        if (!temp)
            /* integer and fraction are 0, we set FP to its max val */
            fppShift = 31;
        else
        {
            /* integer was 0 but fraction is not. FP is 16 for the fraction,
             * + all left zeroes of the fraction. */
            fppShift=16;
            /* count zeroes left of the higher used bit (in order to shift the value such that
             * unused bits may be used for fraction).
             */
            while ((temp & 0x8000) == 0)
            {
                temp = temp << 1;
                fppShift++;
            }
        }
    }

    /*
     * This means that the FM TS register will now be used so that 'fppShift' bits are for
     * fraction and the rest for integer */
    /* now we re-calculate cir and pir_eir with the calculated FP */
    GetInfoRateReg(p_NonPassthroughAlgParam->rateMode, p_NonPassthroughAlgParam->committedInfoRate, tsuInTenthNanos, fppShift, &integer, &fraction);
    *cir = (uint32_t)(integer << 16 | (fraction & 0xFFFF));
    GetInfoRateReg(p_NonPassthroughAlgParam->rateMode, p_NonPassthroughAlgParam->peakOrExcessInfoRate, tsuInTenthNanos, fppShift, &integer, &fraction);
    *pir_eir = (uint32_t)(integer << 16 | (fraction & 0xFFFF));

    *cbs     =  p_NonPassthroughAlgParam->committedBurstSize;
    *pbs_ebs =  p_NonPassthroughAlgParam->peakOrExcessBurstSize;

    /* convert FP as it should be written to reg.
     * 0-15 --> 16-31
     * 16-31 --> 0-15
     */
    *fpp = CalcFPP(fppShift);
}