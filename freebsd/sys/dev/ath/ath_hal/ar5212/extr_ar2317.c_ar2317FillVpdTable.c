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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int int16_t ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  GetLowerUpperIndex (int,int const*,int,int*,int*) ; 

__attribute__((used)) static HAL_BOOL
ar2317FillVpdTable(uint32_t pdGainIdx, int16_t Pmin, int16_t  Pmax,
		   const int16_t *pwrList, const int16_t *VpdList,
		   uint16_t numIntercepts, uint16_t retVpdList[][64])
{
	uint16_t ii, jj, kk;
	int16_t currPwr = (int16_t)(2*Pmin);
	/* since Pmin is pwr*2 and pwrList is 4*pwr */
	uint32_t  idxL, idxR;

	ii = 0;
	jj = 0;

	if (numIntercepts < 2)
		return AH_FALSE;

	while (ii <= (uint16_t)(Pmax - Pmin)) {
		GetLowerUpperIndex(currPwr, pwrList, numIntercepts, 
					 &(idxL), &(idxR));
		if (idxR < 1)
			idxR = 1;			/* extrapolate below */
		if (idxL == (uint32_t)(numIntercepts - 1))
			idxL = numIntercepts - 2;	/* extrapolate above */
		if (pwrList[idxL] == pwrList[idxR])
			kk = VpdList[idxL];
		else
			kk = (uint16_t)
				(((currPwr - pwrList[idxL])*VpdList[idxR]+ 
				  (pwrList[idxR] - currPwr)*VpdList[idxL])/
				 (pwrList[idxR] - pwrList[idxL]));
		retVpdList[pdGainIdx][ii] = kk;
		ii++;
		currPwr += 2;				/* half dB steps */
	}

	return AH_TRUE;
}