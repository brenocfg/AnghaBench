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
typedef  scalar_t__ u_int ;
struct fpn {scalar_t__* fp_mant; int /*<<< orphan*/  fp_exp; } ;

/* Variables and functions */
 int FPC_NUM ; 
 int FPC_ZERO ; 
 int /*<<< orphan*/  FP_LG ; 
 int /*<<< orphan*/  fpu_norm (struct fpn*) ; 

int
fpu_itof(struct fpn *fp, u_int i)
{

	if (i == 0)
		return (FPC_ZERO);
	/*
	 * The value FP_1 represents 2^FP_LG, so set the exponent
	 * there and let normalization fix it up.  Convert negative
	 * numbers to sign-and-magnitude.  Note that this relies on
	 * fpu_norm()'s handling of `supernormals'; see fpu_subr.c.
	 */
	fp->fp_exp = FP_LG;
	fp->fp_mant[0] = (int)i < 0 ? -i : i;
	fp->fp_mant[1] = 0;
	fp->fp_mant[2] = 0;
	fp->fp_mant[3] = 0;
	fpu_norm(fp);
	return (FPC_NUM);
}