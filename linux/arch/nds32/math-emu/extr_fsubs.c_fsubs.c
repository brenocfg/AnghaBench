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
 scalar_t__ B_c ; 
 int B_s ; 
 int /*<<< orphan*/  FP_ADD_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FP_CLS_NAN ; 
 int /*<<< orphan*/  FP_CUR_EXCEPTIONS ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_DECL_S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_PACK_SP (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_SP (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  __FPU_FPCSR ; 

void fsubs(void *ft, void *fa, void *fb)
{

	FP_DECL_S(A);
	FP_DECL_S(B);
	FP_DECL_S(R);
	FP_DECL_EX;

	FP_UNPACK_SP(A, fa);
	FP_UNPACK_SP(B, fb);

	if (B_c != FP_CLS_NAN)
		B_s ^= 1;

	FP_ADD_S(R, A, B);

	FP_PACK_SP(ft, R);

	__FPU_FPCSR |= FP_CUR_EXCEPTIONS;
}