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

/* Variables and functions */
 int /*<<< orphan*/  D ; 
 int /*<<< orphan*/  DRn ; 
 int /*<<< orphan*/  FPUL ; 
 int /*<<< orphan*/  FP_CONV (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_DECL_S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Fn ; 
 int /*<<< orphan*/  Fr ; 
 int /*<<< orphan*/  PACK_D (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  UNPACK_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fcnvsd(struct sh_fpu_soft_struct *fregs, int n)
{
	FP_DECL_EX;
	FP_DECL_S(Fn);
	FP_DECL_D(Fr);
	UNPACK_S(Fn, FPUL);
	FP_CONV(D, S, 2, 1, Fr, Fn);
	PACK_D(DRn, Fr);
	return 0;
}