#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {TYPE_1__* dbell_regs; } ;
struct TYPE_7__ {TYPE_2__* pw_regs; } ;
struct TYPE_6__ {int /*<<< orphan*/  pwsr; } ;
struct TYPE_5__ {int /*<<< orphan*/  dsr; int /*<<< orphan*/  odsr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDSR_CLEAR ; 
 int /*<<< orphan*/  IMSR_CLEAR ; 
 int /*<<< orphan*/  IPWSR_CLEAR ; 
 int /*<<< orphan*/  ODSR_CLEAR ; 
 int /*<<< orphan*/  OMSR_CLEAR ; 
 scalar_t__ RIO_IM0SR ; 
 scalar_t__ RIO_IM1SR ; 
 scalar_t__ RIO_LTLEDCSR ; 
 scalar_t__ RIO_OM0SR ; 
 scalar_t__ RIO_OM1SR ; 
 TYPE_4__* dbell ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* pw ; 
 scalar_t__ rio_regs_win ; 
 scalar_t__ rmu_regs_win ; 

void msg_unit_error_handler(void)
{

	/*XXX: Error recovery is not implemented, we just clear errors */
	out_be32((u32 *)(rio_regs_win + RIO_LTLEDCSR), 0);

	out_be32((u32 *)(rmu_regs_win + RIO_IM0SR), IMSR_CLEAR);
	out_be32((u32 *)(rmu_regs_win + RIO_IM1SR), IMSR_CLEAR);
	out_be32((u32 *)(rmu_regs_win + RIO_OM0SR), OMSR_CLEAR);
	out_be32((u32 *)(rmu_regs_win + RIO_OM1SR), OMSR_CLEAR);

	out_be32(&dbell->dbell_regs->odsr, ODSR_CLEAR);
	out_be32(&dbell->dbell_regs->dsr, IDSR_CLEAR);

	out_be32(&pw->pw_regs->pwsr, IPWSR_CLEAR);
}