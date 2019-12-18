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

/* Variables and functions */

__attribute__((used)) static void rem_kernel(unsigned long long st0, unsigned long long *y,
		       unsigned long long st1, unsigned long long q, int n)
{
	int dummy;
	unsigned long long x;

	x = st0 << n;

	/* Do the required multiplication and subtraction in the one operation */

	/* lsw x -= lsw st1 * lsw q */
	asm volatile ("mull %4; subl %%eax,%0; sbbl %%edx,%1":"=m"
		      (((unsigned *)&x)[0]), "=m"(((unsigned *)&x)[1]),
		      "=a"(dummy)
		      :"2"(((unsigned *)&st1)[0]), "m"(((unsigned *)&q)[0])
		      :"%dx");
	/* msw x -= msw st1 * lsw q */
	asm volatile ("mull %3; subl %%eax,%0":"=m" (((unsigned *)&x)[1]),
		      "=a"(dummy)
		      :"1"(((unsigned *)&st1)[1]), "m"(((unsigned *)&q)[0])
		      :"%dx");
	/* msw x -= lsw st1 * msw q */
	asm volatile ("mull %3; subl %%eax,%0":"=m" (((unsigned *)&x)[1]),
		      "=a"(dummy)
		      :"1"(((unsigned *)&st1)[0]), "m"(((unsigned *)&q)[1])
		      :"%dx");

	*y = x;
}