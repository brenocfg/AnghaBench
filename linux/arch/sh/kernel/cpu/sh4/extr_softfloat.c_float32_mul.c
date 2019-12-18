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
typedef  int /*<<< orphan*/  float32 ;

/* Variables and functions */
 int extractFloat32Exp (int /*<<< orphan*/ ) ; 
 unsigned int extractFloat32Frac (int /*<<< orphan*/ ) ; 
 char extractFloat32Sign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normalizeFloat32Subnormal (unsigned int,int*,unsigned int*) ; 
 int /*<<< orphan*/  packFloat32 (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundAndPackFloat32 (char,int,unsigned int) ; 
 int /*<<< orphan*/  shift64RightJamming (unsigned long long,int,unsigned long long*) ; 

float32 float32_mul(float32 a, float32 b)
{
	char aSign, bSign, zSign;
	int aExp, bExp, zExp;
	unsigned int aSig, bSig;
	unsigned long long zSig64;
	unsigned int zSig;

	aSig = extractFloat32Frac(a);
	aExp = extractFloat32Exp(a);
	aSign = extractFloat32Sign(a);
	bSig = extractFloat32Frac(b);
	bExp = extractFloat32Exp(b);
	bSign = extractFloat32Sign(b);
	zSign = aSign ^ bSign;
	if (aExp == 0) {
		if (aSig == 0)
			return packFloat32(zSign, 0, 0);
		normalizeFloat32Subnormal(aSig, &aExp, &aSig);
	}
	if (bExp == 0) {
		if (bSig == 0)
			return packFloat32(zSign, 0, 0);
		normalizeFloat32Subnormal(bSig, &bExp, &bSig);
	}
	if ((bExp == 0xff && bSig == 0) || (aExp == 0xff && aSig == 0))
		return roundAndPackFloat32(zSign, 0xff, 0);

	zExp = aExp + bExp - 0x7F;
	aSig = (aSig | 0x00800000) << 7;
	bSig = (bSig | 0x00800000) << 8;
	shift64RightJamming(((unsigned long long)aSig) * bSig, 32, &zSig64);
	zSig = zSig64;
	if (0 <= (signed int)(zSig << 1)) {
		zSig <<= 1;
		--zExp;
	}
	return roundAndPackFloat32(zSign, zExp, zSig);

}