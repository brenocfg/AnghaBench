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
typedef  scalar_t__ u_int ;
struct powerpc_exception {scalar_t__ vector; char const* name; } ;

/* Variables and functions */
 scalar_t__ EXC_LAST ; 
 struct powerpc_exception* powerpc_exceptions ; 

__attribute__((used)) static const char *
trapname(u_int vector)
{
	struct	powerpc_exception *pe;

	for (pe = powerpc_exceptions; pe->vector != EXC_LAST; pe++) {
		if (pe->vector == vector)
			return (pe->name);
	}

	return ("unknown");
}