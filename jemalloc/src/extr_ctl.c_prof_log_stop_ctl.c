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
typedef  int /*<<< orphan*/  tsd_t ;

/* Variables and functions */
 int EFAULT ; 
 int ENOENT ; 
 int /*<<< orphan*/  config_prof ; 
 scalar_t__ prof_log_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
prof_log_stop_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	if (!config_prof) {
		return ENOENT;
	}

	if (prof_log_stop(tsd_tsdn(tsd))) {
		return EFAULT;
	}

	return 0;
}