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
typedef  scalar_t__ sbits64 ;
typedef  int bits64 ;

/* Variables and functions */
 int LIT64 (int) ; 
 int /*<<< orphan*/  add128 (int,int,int,int,int*,int*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  mul64To128 (int,int,int*,int*) ; 
 int /*<<< orphan*/  sub128 (int,int,int,int,int*,int*) ; 

__attribute__((used)) static bits64 estimateDiv128To64(bits64 a0, bits64 a1, bits64 b)
{
	bits64 b0, b1;
	bits64 rem0, rem1, term0, term1;
	bits64 z, tmp;
	if (b <= a0)
		return LIT64(0xFFFFFFFFFFFFFFFF);
	b0 = b >> 32;
	tmp = a0;
	do_div(tmp, b0);

	z = (b0 << 32 <= a0) ? LIT64(0xFFFFFFFF00000000) : tmp << 32;
	mul64To128(b, z, &term0, &term1);
	sub128(a0, a1, term0, term1, &rem0, &rem1);
	while (((sbits64) rem0) < 0) {
		z -= LIT64(0x100000000);
		b1 = b << 32;
		add128(rem0, rem1, b0, b1, &rem0, &rem1);
	}
	rem0 = (rem0 << 32) | (rem1 >> 32);
	tmp = rem0;
	do_div(tmp, b0);
	z |= (b0 << 32 <= rem0) ? 0xFFFFFFFF : tmp;
	return z;
}