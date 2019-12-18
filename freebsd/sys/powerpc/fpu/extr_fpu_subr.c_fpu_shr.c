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
struct fpn {scalar_t__ fp_class; int* fp_mant; int fp_sticky; } ;

/* Variables and functions */
 scalar_t__ FPC_NUM ; 
 scalar_t__ FPC_ZERO ; 
 int FP_NMANT ; 
 int /*<<< orphan*/  ISNAN (struct fpn*) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
fpu_shr(struct fpn *fp, int rsh)
{
	u_int m0, m1, m2, m3, s;
	int lsh;

#ifdef DIAGNOSTIC
	if (rsh <= 0 || (fp->fp_class != FPC_NUM && !ISNAN(fp)))
		panic("fpu_rightshift 1");
#endif

	m0 = fp->fp_mant[0];
	m1 = fp->fp_mant[1];
	m2 = fp->fp_mant[2];
	m3 = fp->fp_mant[3];

	/* If shifting all the bits out, take a shortcut. */
	if (rsh >= FP_NMANT) {
#ifdef DIAGNOSTIC
		if ((m0 | m1 | m2 | m3) == 0)
			panic("fpu_rightshift 2");
#endif
		fp->fp_mant[0] = 0;
		fp->fp_mant[1] = 0;
		fp->fp_mant[2] = 0;
		fp->fp_mant[3] = 0;
#ifdef notdef
		if ((m0 | m1 | m2 | m3) == 0)
			fp->fp_class = FPC_ZERO;
		else
#endif
			fp->fp_sticky = 1;
		return (1);
	}

	/* Squish out full words. */
	s = fp->fp_sticky;
	if (rsh >= 32 * 3) {
		s |= m3 | m2 | m1;
		m3 = m0, m2 = 0, m1 = 0, m0 = 0;
	} else if (rsh >= 32 * 2) {
		s |= m3 | m2;
		m3 = m1, m2 = m0, m1 = 0, m0 = 0;
	} else if (rsh >= 32) {
		s |= m3;
		m3 = m2, m2 = m1, m1 = m0, m0 = 0;
	}

	/* Handle any remaining partial word. */
	if ((rsh &= 31) != 0) {
		lsh = 32 - rsh;
		s |= m3 << lsh;
		m3 = (m3 >> rsh) | (m2 << lsh);
		m2 = (m2 >> rsh) | (m1 << lsh);
		m1 = (m1 >> rsh) | (m0 << lsh);
		m0 >>= rsh;
	}
	fp->fp_mant[0] = m0;
	fp->fp_mant[1] = m1;
	fp->fp_mant[2] = m2;
	fp->fp_mant[3] = m3;
	fp->fp_sticky = s;
	return (s);
}