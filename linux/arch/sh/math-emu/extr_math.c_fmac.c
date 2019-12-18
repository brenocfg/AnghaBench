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
struct sh_fpu_soft_struct {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F0 ; 
 int /*<<< orphan*/  FP_ADD_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_DECL_S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_MUL_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FR0 ; 
 int /*<<< orphan*/  FRm ; 
 int /*<<< orphan*/  FRn ; 
 int /*<<< orphan*/  Fm ; 
 int /*<<< orphan*/  Fn ; 
 int /*<<< orphan*/  Fr ; 
 int /*<<< orphan*/  Ft ; 
 int /*<<< orphan*/  PACK_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNPACK_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fmac(struct sh_fpu_soft_struct *fregs, struct pt_regs *regs, int m, int n)
{
	FP_DECL_EX;
	FP_DECL_S(Fr);
	FP_DECL_S(Ft);
	FP_DECL_S(F0);
	FP_DECL_S(Fm);
	FP_DECL_S(Fn);
	UNPACK_S(F0, FR0);
	UNPACK_S(Fm, FRm);
	UNPACK_S(Fn, FRn);
	FP_MUL_S(Ft, Fm, F0);
	FP_ADD_S(Fr, Fn, Ft);
	PACK_S(FRn, Fr);
	return 0;
}