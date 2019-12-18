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
 int x86_mtrrtype (int) ; 

__attribute__((used)) static int
x86_mrt2mtrr(int flags, int oldval)
{
	int val;

	if ((val = x86_mtrrtype(flags)) == -1)
		return (oldval & 0xff);
	return (val & 0xff);
}