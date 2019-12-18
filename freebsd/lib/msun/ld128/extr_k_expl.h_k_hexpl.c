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

/* Variables and functions */
 int /*<<< orphan*/  SET_FLOAT_WORD (float,int) ; 
 int /*<<< orphan*/  __k_expl (long double,long double*,long double*,int*) ; 

__attribute__((used)) static inline void
k_hexpl(long double x, long double *hip, long double *lop)
{
	float twopkm1;
	int k;

	__k_expl(x, hip, lop, &k);
	SET_FLOAT_WORD(twopkm1, 0x3f800000 + ((k - 1) << 23));
	*hip *= twopkm1;
	*lop *= twopkm1;
}