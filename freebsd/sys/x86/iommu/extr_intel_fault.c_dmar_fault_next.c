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
struct dmar_unit {int fault_log_size; } ;

/* Variables and functions */

__attribute__((used)) static int
dmar_fault_next(struct dmar_unit *unit, int faultp)
{

	faultp += 2;
	if (faultp == unit->fault_log_size)
		faultp = 0;
	return (faultp);
}