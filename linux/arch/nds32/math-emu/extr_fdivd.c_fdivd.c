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
 scalar_t__ A_c ; 
 int /*<<< orphan*/  B ; 
 scalar_t__ B_c ; 
 scalar_t__ FP_CLS_ZERO ; 
 int /*<<< orphan*/  FP_CUR_EXCEPTIONS ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_DIV_D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_EX_DIVZERO ; 
 int /*<<< orphan*/  FP_PACK_DP (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_SET_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_DP (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  __FPU_FPCSR ; 

void fdivd(void *ft, void *fa, void *fb)
{
	FP_DECL_D(A);
	FP_DECL_D(B);
	FP_DECL_D(R);
	FP_DECL_EX;

	FP_UNPACK_DP(A, fa);
	FP_UNPACK_DP(B, fb);

	if (B_c == FP_CLS_ZERO && A_c != FP_CLS_ZERO)
		FP_SET_EXCEPTION(FP_EX_DIVZERO);

	FP_DIV_D(R, A, B);

	FP_PACK_DP(ft, R);

	__FPU_FPCSR |= FP_CUR_EXCEPTIONS;
}