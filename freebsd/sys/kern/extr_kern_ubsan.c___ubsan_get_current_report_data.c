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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

void
__ubsan_get_current_report_data(const char **ppOutIssueKind, const char **ppOutMessage, const char **ppOutFilename, uint32_t *pOutLine, uint32_t *pOutCol, char **ppOutMemoryAddr)
{
	/*
	 * Unimplemented.
	 *
	 * The __ubsan_on_report() feature is non trivial to implement in a
	 * shared code between the kernel and userland. It's also opening
	 * new sets of potential problems as we are not expected to slow down
	 * execution of certain kernel subsystems (synchronization issues,
	 * interrupt handling etc).
	 *
	 * A proper solution would need probably a lock-free bounded queue built
	 * with atomic operations with the property of miltiple consumers and
	 * multiple producers. Maintaining and validating such code is not
	 * worth the effort.
	 *
	 * A legitimate user - besides testing framework - is a debugger plugin
	 * intercepting reports from the UBSan instrumentation. For such
	 * scenarios it is better to run the Clang/GCC version.
	 */
}