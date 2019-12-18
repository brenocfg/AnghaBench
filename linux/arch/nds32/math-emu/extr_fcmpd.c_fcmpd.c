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
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  B ; 
 int /*<<< orphan*/  FP_CMP_D (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_UNPACK_DP (int /*<<< orphan*/ ,void*) ; 
 long SF_CGT ; 
 int /*<<< orphan*/  SF_CUN ; 

int fcmpd(void *ft, void *fa, void *fb, int cmpop)
{
	FP_DECL_D(A);
	FP_DECL_D(B);
	FP_DECL_EX;
	long cmp;

	FP_UNPACK_DP(A, fa);
	FP_UNPACK_DP(B, fb);

	FP_CMP_D(cmp, A, B, SF_CUN);
	cmp += 2;
	if (cmp == SF_CGT)
		*(long *)ft = 0;
	else
		*(long *)ft = (cmp & cmpop) ? 1 : 0;

	return 0;
}