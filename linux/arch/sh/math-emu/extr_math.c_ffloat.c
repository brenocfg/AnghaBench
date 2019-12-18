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
 int /*<<< orphan*/  EMU_FLOAT_X (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FPSCR_PR ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FRn ; 
 int /*<<< orphan*/  S ; 

__attribute__((used)) static int ffloat(struct sh_fpu_soft_struct *fregs, int n)
{
	FP_DECL_EX;

	if (FPSCR_PR)
		EMU_FLOAT_X(D, DRn);
	else
		EMU_FLOAT_X(S, FRn);

	return 0;
}