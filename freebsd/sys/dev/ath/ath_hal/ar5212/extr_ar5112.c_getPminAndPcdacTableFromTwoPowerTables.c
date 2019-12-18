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
typedef  int uint16_t ;
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static int16_t
getPminAndPcdacTableFromTwoPowerTables(int16_t *pwrTableLXpdT4,
	int16_t *pwrTableHXpdT4, uint16_t retVals[], int16_t *pMid)
{
    int16_t     ii, jj, jjMax;
    int16_t     pMin, pMax, currPower;
    int16_t     *pwrTableT4;
    uint16_t    msbFlag = 0x40;  // turns on the 7th bit of the pcdac

    /* If the spread is > 31.5dB, keep the upper 31.5dB range */
    if ((pwrTableLXpdT4[63] - pwrTableHXpdT4[0]) > 126) {
        pMin = pwrTableLXpdT4[63] - 126;
    } else {
        pMin = pwrTableHXpdT4[0];
    }

    pMax = pwrTableLXpdT4[63];
    jjMax = 63;
    /* Search for highest pcdac 0.25dB below maxPower */
    while ((pwrTableLXpdT4[jjMax] > (pMax - 1) ) && (jjMax >= 0)){
        jjMax--;
    }

    *pMid = pwrTableHXpdT4[63];
    jj = jjMax;
    ii = 63;
    currPower = pMax;
    pwrTableT4 = &(pwrTableLXpdT4[0]);
    while (ii >= 0) {
        if ((currPower <= *pMid) || ( (jj == 0) && (msbFlag == 0x40))){
            msbFlag = 0x00;
            pwrTableT4 = &(pwrTableHXpdT4[0]);
            jj = 63;
        }
        while ((jj > 0) && (pwrTableT4[jj] >= currPower)) {
            jj--;
        }
        if ((jj == 0) && (msbFlag == 0x00)) {
            while (ii >= 0) {
                retVals[ii] = retVals[ii+1];
                ii--;
            }
            break;
        }
        retVals[ii] = jj | msbFlag;
        currPower -= 2;  // corresponds to a 0.5dB step
        ii--;
    }
    return pMin;
}