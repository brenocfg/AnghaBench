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
typedef  union descriptor {int dummy; } descriptor ;
struct i386_ldt_args {int start; int num; union descriptor* descs; } ;

/* Variables and functions */
 int /*<<< orphan*/  I386_SET_LDT ; 
 int sysarch (int /*<<< orphan*/ ,struct i386_ldt_args*) ; 

int
i386_set_ldt(int start, union descriptor *descs, int num)
{
	struct i386_ldt_args p;

	p.start = start;
	p.descs = descs;
	p.num   = num;

	return sysarch(I386_SET_LDT, &p);
}