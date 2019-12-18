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
 int /*<<< orphan*/  __cvmx_shared_end ; 
 int /*<<< orphan*/  __cvmx_shared_start ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void shutdown_cvmx_shared(void)
{
    unsigned long shared_size = &__cvmx_shared_end - &__cvmx_shared_start;
    if (shared_size)
        munmap(&__cvmx_shared_start, shared_size);
}