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
typedef  int /*<<< orphan*/  float64 ;

/* Variables and functions */
 int extractFloat64Exp (int /*<<< orphan*/ ) ; 
 unsigned long long extractFloat64Frac (int /*<<< orphan*/ ) ; 
 char extractFloat64Sign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul64To128 (unsigned long long,unsigned long long,unsigned long long*,unsigned long long*) ; 
 int /*<<< orphan*/  normalizeFloat64Subnormal (unsigned long long,int*,unsigned long long*) ; 
 int /*<<< orphan*/  packFloat64 (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundAndPackFloat64 (char,int,unsigned long long) ; 

float64 float64_mul(float64 a, float64 b)
{
	char aSign, bSign, zSign;
	int aExp, bExp, zExp;
	unsigned long long int aSig, bSig, zSig0, zSig1;

	aSig = extractFloat64Frac(a);
	aExp = extractFloat64Exp(a);
	aSign = extractFloat64Sign(a);
	bSig = extractFloat64Frac(b);
	bExp = extractFloat64Exp(b);
	bSign = extractFloat64Sign(b);
	zSign = aSign ^ bSign;

	if (aExp == 0) {
		if (aSig == 0)
			return packFloat64(zSign, 0, 0);
		normalizeFloat64Subnormal(aSig, &aExp, &aSig);
	}
	if (bExp == 0) {
		if (bSig == 0)
			return packFloat64(zSign, 0, 0);
		normalizeFloat64Subnormal(bSig, &bExp, &bSig);
	}
	if ((aExp == 0x7ff && aSig == 0) || (bExp == 0x7ff && bSig == 0))
		return roundAndPackFloat64(zSign, 0x7ff, 0);

	zExp = aExp + bExp - 0x3FF;
	aSig = (aSig | 0x0010000000000000LL) << 10;
	bSig = (bSig | 0x0010000000000000LL) << 11;
	mul64To128(aSig, bSig, &zSig0, &zSig1);
	zSig0 |= (zSig1 != 0);
	if (0 <= (signed long long int)(zSig0 << 1)) {
		zSig0 <<= 1;
		--zExp;
	}
	return roundAndPackFloat64(zSign, zExp, zSig0);
}