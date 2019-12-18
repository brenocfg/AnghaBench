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
 int SC_KERNEL_CONS_ATTR ; 
 size_t curcpu ; 
 size_t nitems (int*) ; 
 int /*<<< orphan*/ * sc_console ; 
 int* sc_kattrtab ; 

__attribute__((used)) static int
sc_kattr(void)
{
    if (sc_console == NULL)
	return (SC_KERNEL_CONS_ATTR);	/* for very early, before pcpu */
    return (sc_kattrtab[curcpu % nitems(sc_kattrtab)]);
}