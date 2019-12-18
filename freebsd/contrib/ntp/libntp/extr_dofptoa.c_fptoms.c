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
typedef  scalar_t__ u_fp ;
typedef  scalar_t__ s_fp ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 char* dofptoa (scalar_t__,int,short,int /*<<< orphan*/ ) ; 

char *
fptoms(
	s_fp	fpv,
	short	ndec
	)
{
	u_fp	plusfp;
	int	neg;

	neg = (fpv < 0);
	if (neg) {
		plusfp = (u_fp)(-fpv);
	} else {
		plusfp = (u_fp)fpv;
	}

	return dofptoa(plusfp, neg, ndec, TRUE);
}