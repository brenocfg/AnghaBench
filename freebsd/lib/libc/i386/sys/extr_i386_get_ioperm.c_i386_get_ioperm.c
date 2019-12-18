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
 int /*<<< orphan*/  I386_GET_IOPERM ; 
 int sysarch (int /*<<< orphan*/ ,struct i386_ioperm_args*) ; 

int
i386_get_ioperm(unsigned int start, unsigned int *length, int *enable)
{
	struct i386_ioperm_args p;
	int error;

	p.start = start;
	p.length = *length;
	p.enable = *enable;

	error = sysarch(I386_GET_IOPERM, &p);

	*length = p.length;
	*enable = p.enable;

	return (error);
}