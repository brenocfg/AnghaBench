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
struct thread {struct pcb* td_pcb; } ;
struct pcb {int /*<<< orphan*/  pcb_dr7; int /*<<< orphan*/  pcb_dr6; int /*<<< orphan*/  pcb_dr3; int /*<<< orphan*/  pcb_dr2; int /*<<< orphan*/  pcb_dr1; int /*<<< orphan*/  pcb_dr0; } ;
struct dbreg {int /*<<< orphan*/ * dr; } ;

/* Variables and functions */
 int /*<<< orphan*/  rdr0 () ; 
 int /*<<< orphan*/  rdr1 () ; 
 int /*<<< orphan*/  rdr2 () ; 
 int /*<<< orphan*/  rdr3 () ; 
 int /*<<< orphan*/  rdr6 () ; 
 int /*<<< orphan*/  rdr7 () ; 

int
fill_dbregs(struct thread *td, struct dbreg *dbregs)
{
	struct pcb *pcb;

	if (td == NULL) {
		dbregs->dr[0] = rdr0();
		dbregs->dr[1] = rdr1();
		dbregs->dr[2] = rdr2();
		dbregs->dr[3] = rdr3();
		dbregs->dr[6] = rdr6();
		dbregs->dr[7] = rdr7();
	} else {
		pcb = td->td_pcb;
		dbregs->dr[0] = pcb->pcb_dr0;
		dbregs->dr[1] = pcb->pcb_dr1;
		dbregs->dr[2] = pcb->pcb_dr2;
		dbregs->dr[3] = pcb->pcb_dr3;
		dbregs->dr[6] = pcb->pcb_dr6;
		dbregs->dr[7] = pcb->pcb_dr7;
	}
	dbregs->dr[4] = 0;
	dbregs->dr[5] = 0;
	return (0);
}