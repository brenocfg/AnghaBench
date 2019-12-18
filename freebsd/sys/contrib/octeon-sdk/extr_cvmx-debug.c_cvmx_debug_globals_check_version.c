#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ version; } ;

/* Variables and functions */
 scalar_t__ CVMX_DEBUG_GLOBALS_VERSION ; 
 TYPE_1__* cvmx_debug_globals ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void cvmx_debug_globals_check_version(void)
{
    if (cvmx_debug_globals->version != CVMX_DEBUG_GLOBALS_VERSION)
    {
        cvmx_dprintf("Wrong version on the globals struct spinining; expected %d, got:  %d.\n", (int)CVMX_DEBUG_GLOBALS_VERSION, (int)(cvmx_debug_globals->version));
#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
        panic("Wrong version.\n");
#endif
        while (1)
            ;
    }
}