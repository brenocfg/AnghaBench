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
 int /*<<< orphan*/  READONLY () ; 
 int /*<<< orphan*/  WRITEONLY () ; 
 int /*<<< orphan*/  tcache_available (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcache_flush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
thread_tcache_flush_ctl(tsd_t *tsd, const size_t *mib,
    size_t miblen, void *oldp, size_t *oldlenp, void *newp,
    size_t newlen) {
	int ret;

	if (!tcache_available(tsd)) {
		ret = EFAULT;
		goto label_return;
	}

	READONLY();
	WRITEONLY();

	tcache_flush(tsd);

	ret = 0;
label_return:
	return ret;
}