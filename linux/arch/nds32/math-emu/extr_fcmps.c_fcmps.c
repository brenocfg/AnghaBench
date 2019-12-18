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
 int /*<<< orphan*/  FP_CMP_S (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_DECL_S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_SP (int /*<<< orphan*/ ,void*) ; 
 long SF_CGT ; 
 int /*<<< orphan*/  SF_CUN ; 

int fcmps(void *ft, void *fa, void *fb, int cmpop)
{
	FP_DECL_S(A);
	FP_DECL_S(B);
	FP_DECL_EX;
	long cmp;

	FP_UNPACK_SP(A, fa);
	FP_UNPACK_SP(B, fb);

	FP_CMP_S(cmp, A, B, SF_CUN);
	cmp += 2;
	if (cmp == SF_CGT)
		*(int *)ft = 0x0;
	else
		*(int *)ft = (cmp & cmpop) ? 0x1 : 0x0;

	return 0;
}