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
typedef  scalar_t__ sbits32 ;
typedef  int int8 ;
typedef  int int16 ;
typedef  scalar_t__ float32 ;
typedef  int flag ;
typedef  int bits32 ;
typedef  int bits16 ;

/* Variables and functions */
 int FPSCR_CAUSE_INEXACT ; 
 int FPSCR_CAUSE_OVERFLOW ; 
 int FPSCR_CAUSE_UNDERFLOW ; 
 scalar_t__ FPSCR_RM_NEAREST ; 
 int /*<<< orphan*/  float_raise (int) ; 
 scalar_t__ float_rounding_mode () ; 
 scalar_t__ packFloat32 (int,int,int) ; 
 int /*<<< orphan*/  shift32RightJamming (int,int,int*) ; 

__attribute__((used)) static float32 roundAndPackFloat32(flag zSign, int16 zExp, bits32 zSig)
{
	flag roundNearestEven;
	int8 roundIncrement, roundBits;
	flag isTiny;

	/* SH4 has only 2 rounding modes - round to nearest and round to zero */
	roundNearestEven = (float_rounding_mode() == FPSCR_RM_NEAREST);
	roundIncrement = 0x40;
	if (!roundNearestEven) {
		roundIncrement = 0;
	}
	roundBits = zSig & 0x7F;
	if (0xFD <= (bits16) zExp) {
		if ((0xFD < zExp)
		    || ((zExp == 0xFD)
			&& ((sbits32) (zSig + roundIncrement) < 0))
		    ) {
			float_raise(FPSCR_CAUSE_OVERFLOW | FPSCR_CAUSE_INEXACT);
			return packFloat32(zSign, 0xFF,
					   0) - (roundIncrement == 0);
		}
		if (zExp < 0) {
			isTiny = (zExp < -1)
			    || (zSig + roundIncrement < 0x80000000);
			shift32RightJamming(zSig, -zExp, &zSig);
			zExp = 0;
			roundBits = zSig & 0x7F;
			if (isTiny && roundBits)
				float_raise(FPSCR_CAUSE_UNDERFLOW);
		}
	}
	if (roundBits)
		float_raise(FPSCR_CAUSE_INEXACT);
	zSig = (zSig + roundIncrement) >> 7;
	zSig &= ~(((roundBits ^ 0x40) == 0) & roundNearestEven);
	if (zSig == 0)
		zExp = 0;
	return packFloat32(zSign, zExp, zSig);

}