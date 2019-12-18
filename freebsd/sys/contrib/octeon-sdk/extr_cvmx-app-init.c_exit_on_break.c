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
struct TYPE_2__ {unsigned int core_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  __octeon_uart_unlock () ; 
 int /*<<< orphan*/  cvmx_coremask_barrier_sync (unsigned int) ; 
 scalar_t__ cvmx_coremask_first_core (unsigned int) ; 
 TYPE_1__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exit_on_break(void)
{
#if OCTEON_APP_INIT_H_VERSION >= 4
    unsigned int coremask = cvmx_sysinfo_get()->core_mask;

    cvmx_coremask_barrier_sync(coremask);
    if (cvmx_coremask_first_core(coremask))
      __octeon_uart_unlock();
#endif

    exit(0);
}