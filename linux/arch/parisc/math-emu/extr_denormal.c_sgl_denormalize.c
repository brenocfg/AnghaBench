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
typedef  scalar_t__ boolean ;

/* Variables and functions */
 scalar_t__ FALSE ; 
#define  ROUNDMINUS 130 
#define  ROUNDNEAREST 129 
#define  ROUNDPLUS 128 
 int SGL_WRAP ; 
 int /*<<< orphan*/  Sgl_denormalize (unsigned int,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int Sgl_exponent (unsigned int) ; 
 int /*<<< orphan*/  Sgl_increment (unsigned int) ; 
 int /*<<< orphan*/  Sgl_isone_lowmantissa (unsigned int) ; 
 int /*<<< orphan*/  Sgl_set_sign (unsigned int,int) ; 
 int Sgl_sign (unsigned int) ; 

void
sgl_denormalize(unsigned int *sgl_opnd, boolean *inexactflag, int rmode)
{
	unsigned int opnd;
	int sign, exponent;
	boolean guardbit = FALSE, stickybit, inexact;

	opnd = *sgl_opnd;
	stickybit = *inexactflag;
        exponent = Sgl_exponent(opnd) - SGL_WRAP;
        sign = Sgl_sign(opnd);
	Sgl_denormalize(opnd,exponent,guardbit,stickybit,inexact);
	if (inexact) {
	    switch (rmode) {
	      case ROUNDPLUS:
		if (sign == 0) {
			Sgl_increment(opnd);
		}
		break;
	      case ROUNDMINUS:
		if (sign != 0) {
			Sgl_increment(opnd);
		}
		break;
	      case ROUNDNEAREST:
		if (guardbit && (stickybit || 
		       Sgl_isone_lowmantissa(opnd))) {
			   Sgl_increment(opnd);
		}
		break;
	    }
	}
	Sgl_set_sign(opnd,sign);
	*sgl_opnd = opnd;
	*inexactflag = inexact;
	return;
}