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
struct i386_ioperm_args {unsigned int start; unsigned int length; int enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  I386_SET_IOPERM ; 
 int sysarch (int /*<<< orphan*/ ,struct i386_ioperm_args*) ; 

int
i386_set_ioperm(unsigned int start, unsigned int length, int enable)
{
	struct i386_ioperm_args p;

	p.start = start;
	p.length = length;
	p.enable = enable;

	return (sysarch(I386_SET_IOPERM, &p));
}