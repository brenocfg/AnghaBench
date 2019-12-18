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
struct dmatest_info {int /*<<< orphan*/  did_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  run_pending_tests (struct dmatest_info*) ; 

__attribute__((used)) static void start_threaded_tests(struct dmatest_info *info)
{
	/* we might be called early to set run=, defer running until all
	 * parameters have been evaluated
	 */
	if (!info->did_init)
		return;

	run_pending_tests(info);
}