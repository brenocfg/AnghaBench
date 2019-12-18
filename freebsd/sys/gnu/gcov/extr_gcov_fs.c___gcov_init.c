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
struct gcov_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GCOV_ADD ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  gcov_event (int /*<<< orphan*/ ,struct gcov_info*) ; 
 scalar_t__ gcov_events_enabled ; 
 int /*<<< orphan*/  gcov_info_link (struct gcov_info*) ; 
 unsigned int gcov_info_version (struct gcov_info*) ; 
 int /*<<< orphan*/  gcov_mtx ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
__gcov_init(struct gcov_info *info)
{
	static unsigned int gcov_version;

	mtx_lock(&gcov_mtx);
	if (gcov_version == 0) {
		gcov_version = gcov_info_version(info);
		/*
		 * Printing gcc's version magic may prove useful for debugging
		 * incompatibility reports.
		 */
		log(LOG_INFO, "version magic: 0x%x\n", gcov_version);
	}
	/*
	 * Add new profiling data structure to list and inform event
	 * listener.
	 */
	gcov_info_link(info);
	if (gcov_events_enabled)
		gcov_event(GCOV_ADD, info);
	mtx_unlock(&gcov_mtx);
}