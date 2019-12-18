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
typedef  scalar_t__ uint32_t ;
struct fpn {int dummy; } ;
struct fpemu {int /*<<< orphan*/  fe_cx; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPSCR_OX ; 
 int /*<<< orphan*/  FPSCR_UX ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ fpu_ftox (struct fpemu*,struct fpn*,scalar_t__*) ; 

__attribute__((used)) static int
spe_to_int(struct fpemu *fpemu, struct fpn *fpn, uint32_t *val, int sign)
{
	uint32_t res[2];

	res[0] = fpu_ftox(fpemu, fpn, res);
	if (res[0] != UINT_MAX && res[0] != 0)
		fpemu->fe_cx |= FPSCR_OX;
	else if (sign == 0 && res[0] != 0)
		fpemu->fe_cx |= FPSCR_UX;
	else
		*val = res[1];

	return (0);
}