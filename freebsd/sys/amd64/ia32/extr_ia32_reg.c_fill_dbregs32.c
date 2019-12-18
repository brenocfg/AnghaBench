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
struct dbreg32 {int /*<<< orphan*/ * dr; } ;
struct dbreg {int /*<<< orphan*/ * dr; } ;

/* Variables and functions */
 int fill_dbregs (struct thread*,struct dbreg*) ; 

int
fill_dbregs32(struct thread *td, struct dbreg32 *regs)
{
	struct dbreg dr;
	int err, i;

	err = fill_dbregs(td, &dr);
	for (i = 0; i < 8; i++)
		regs->dr[i] = dr.dr[i];
	return (err);
}