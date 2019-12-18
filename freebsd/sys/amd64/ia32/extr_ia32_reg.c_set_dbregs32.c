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
struct thread {int dummy; } ;
struct dbreg32 {scalar_t__* dr; } ;
struct dbreg {scalar_t__* dr; } ;

/* Variables and functions */
 int set_dbregs (struct thread*,struct dbreg*) ; 

int
set_dbregs32(struct thread *td, struct dbreg32 *regs)
{
	struct dbreg dr;
	int i;

	for (i = 0; i < 8; i++)
		dr.dr[i] = regs->dr[i];
	for (i = 8; i < 16; i++)
		dr.dr[i] = 0;
	return (set_dbregs(td, &dr));
}