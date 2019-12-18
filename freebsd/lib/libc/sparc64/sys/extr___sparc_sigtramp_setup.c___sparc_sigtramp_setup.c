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
 int /*<<< orphan*/  SPARC_SIGTRAMP_INSTALL ; 
 int /*<<< orphan*/  sia ; 
 int /*<<< orphan*/  sysarch (int /*<<< orphan*/ ,void*) ; 

void
__sparc_sigtramp_setup(void)
{

	sysarch(SPARC_SIGTRAMP_INSTALL, (void *)&sia);
}