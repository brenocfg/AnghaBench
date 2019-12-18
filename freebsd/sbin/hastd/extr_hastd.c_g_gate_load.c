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
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  EX_OSERR ; 
 scalar_t__ errno ; 
 int kldload (char*) ; 
 int modfind (char*) ; 
 int /*<<< orphan*/  pjdlog_exit (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
g_gate_load(void)
{

	if (modfind("g_gate") == -1) {
		/* Not present in kernel, try loading it. */
		if (kldload("geom_gate") == -1 || modfind("g_gate") == -1) {
			if (errno != EEXIST) {
				pjdlog_exit(EX_OSERR,
				    "Unable to load geom_gate module");
			}
		}
	}
}