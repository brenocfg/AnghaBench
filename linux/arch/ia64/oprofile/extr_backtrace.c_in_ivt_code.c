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
typedef  unsigned long u_long ;

/* Variables and functions */

__attribute__((used)) static __inline__ int in_ivt_code(unsigned long pc)
{
	extern char ia64_ivt[];
	return (pc >= (u_long)ia64_ivt && pc < (u_long)ia64_ivt+32768);
}