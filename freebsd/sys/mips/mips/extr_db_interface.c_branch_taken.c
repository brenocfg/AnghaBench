#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  register_t ;
typedef  scalar_t__ db_addr_t ;
struct TYPE_6__ {TYPE_2__* td_pcb; } ;
struct TYPE_4__ {int /*<<< orphan*/  fsr; } ;
struct TYPE_5__ {TYPE_1__ pcb_regs; } ;

/* Variables and functions */
 scalar_t__ MipsEmulateBranch (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* curthread ; 
 int /*<<< orphan*/  kdb_frame ; 

db_addr_t
branch_taken(int inst, db_addr_t pc)
{
	db_addr_t ra;
	register_t fpucsr;

	/* TBD: when is fsr set */
	fpucsr = (curthread) ? curthread->td_pcb->pcb_regs.fsr : 0;
	ra = (db_addr_t)MipsEmulateBranch(kdb_frame, pc, fpucsr, 0);
	return (ra);
}