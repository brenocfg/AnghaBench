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
typedef  int u_int ;
struct fpn {int fp_exp; int* fp_mant; int /*<<< orphan*/  fp_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPC_ZERO ; 
 int FP_1 ; 

void
fpu_norm(struct fpn *fp)
{
	u_int m0, m1, m2, m3, top, sup, nrm;
	int lsh, rsh, exp;

	exp = fp->fp_exp;
	m0 = fp->fp_mant[0];
	m1 = fp->fp_mant[1];
	m2 = fp->fp_mant[2];
	m3 = fp->fp_mant[3];

	/* Handle severe subnormals with 32-bit moves. */
	if (m0 == 0) {
		if (m1)
			m0 = m1, m1 = m2, m2 = m3, m3 = 0, exp -= 32;
		else if (m2)
			m0 = m2, m1 = m3, m2 = 0, m3 = 0, exp -= 2 * 32;
		else if (m3)
			m0 = m3, m1 = 0, m2 = 0, m3 = 0, exp -= 3 * 32;
		else {
			fp->fp_class = FPC_ZERO;
			return;
		}
	}

	/* Now fix any supernormal or remaining subnormal. */
	nrm = FP_1;
	sup = nrm << 1;
	if (m0 >= sup) {
		/*
		 * We have a supernormal number.  We need to shift it right.
		 * We may assume m3==0.
		 */
		for (rsh = 1, top = m0 >> 1; top >= sup; rsh++)	/* XXX slow */
			top >>= 1;
		exp += rsh;
		lsh = 32 - rsh;
		m3 = m2 << lsh;
		m2 = (m2 >> rsh) | (m1 << lsh);
		m1 = (m1 >> rsh) | (m0 << lsh);
		m0 = top;
	} else if (m0 < nrm) {
		/*
		 * We have a regular denorm (a subnormal number), and need
		 * to shift it left.
		 */
		for (lsh = 1, top = m0 << 1; top < nrm; lsh++)	/* XXX slow */
			top <<= 1;
		exp -= lsh;
		rsh = 32 - lsh;
		m0 = top | (m1 >> rsh);
		m1 = (m1 << lsh) | (m2 >> rsh);
		m2 = (m2 << lsh) | (m3 >> rsh);
		m3 <<= lsh;
	}

	fp->fp_exp = exp;
	fp->fp_mant[0] = m0;
	fp->fp_mant[1] = m1;
	fp->fp_mant[2] = m2;
	fp->fp_mant[3] = m3;
}