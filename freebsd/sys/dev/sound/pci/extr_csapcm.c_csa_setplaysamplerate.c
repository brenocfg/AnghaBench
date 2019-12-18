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
typedef  int u_long ;
typedef  int /*<<< orphan*/  csa_res ;

/* Variables and functions */
 int /*<<< orphan*/  BA1_PPI ; 
 int /*<<< orphan*/  BA1_PSRC ; 
 int GOF_PER_SEC ; 
 int /*<<< orphan*/  csa_writemem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
csa_setplaysamplerate(csa_res *resp, u_long ulInRate)
{
	u_long ulTemp1, ulTemp2;
	u_long ulPhiIncr;
	u_long ulCorrectionPerGOF, ulCorrectionPerSec;
	u_long ulOutRate;

	ulOutRate = 48000;

	/*
	 * Compute the values used to drive the actual sample rate conversion.
	 * The following formulas are being computed, using inline assembly
	 * since we need to use 64 bit arithmetic to compute the values:
	 *
	 *     ulPhiIncr = floor((Fs,in * 2^26) / Fs,out)
	 *     ulCorrectionPerGOF = floor((Fs,in * 2^26 - Fs,out * ulPhiIncr) /
	 *                                GOF_PER_SEC)
	 *     ulCorrectionPerSec = Fs,in * 2^26 - Fs,out * phiIncr -
	 *                          GOF_PER_SEC * ulCorrectionPerGOF
	 *
	 * i.e.
	 *
	 *     ulPhiIncr:ulOther = dividend:remainder((Fs,in * 2^26) / Fs,out)
	 *     ulCorrectionPerGOF:ulCorrectionPerSec =
	 *         dividend:remainder(ulOther / GOF_PER_SEC)
	 */
	ulTemp1 = ulInRate << 16;
	ulPhiIncr = ulTemp1 / ulOutRate;
	ulTemp1 -= ulPhiIncr * ulOutRate;
	ulTemp1 <<= 10;
	ulPhiIncr <<= 10;
	ulTemp2 = ulTemp1 / ulOutRate;
	ulPhiIncr += ulTemp2;
	ulTemp1 -= ulTemp2 * ulOutRate;
	ulCorrectionPerGOF = ulTemp1 / GOF_PER_SEC;
	ulTemp1 -= ulCorrectionPerGOF * GOF_PER_SEC;
	ulCorrectionPerSec = ulTemp1;

	/*
	 * Fill in the SampleRateConverter control block.
	 */
	csa_writemem(resp, BA1_PSRC, ((ulCorrectionPerSec << 16) & 0xFFFF0000) | (ulCorrectionPerGOF & 0xFFFF));
	csa_writemem(resp, BA1_PPI, ulPhiIncr);
}