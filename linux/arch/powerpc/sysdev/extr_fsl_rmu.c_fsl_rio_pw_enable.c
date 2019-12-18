#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rio_mport {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pw_regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  pwmr; } ;

/* Variables and functions */
 int /*<<< orphan*/  RIO_IPWMR_PWE ; 
 int /*<<< orphan*/  in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* pw ; 

int fsl_rio_pw_enable(struct rio_mport *mport, int enable)
{
	u32 rval;

	rval = in_be32(&pw->pw_regs->pwmr);

	if (enable)
		rval |= RIO_IPWMR_PWE;
	else
		rval &= ~RIO_IPWMR_PWE;

	out_be32(&pw->pw_regs->pwmr, rval);

	return 0;
}